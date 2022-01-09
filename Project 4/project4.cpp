#include <iomanip>
#include <deque>
#include <iostream>
#include <getopt.h>
#include <string>
#include <deque>
#include <vector>
#include <sstream>
#include <functional>
#include <cstdlib>
#include <cmath>
#include <limits>

using namespace std;

int big = std::numeric_limits<int>::max();
int numv;
static struct option long_options[]{
	{ "help", no_argument, nullptr, 'h' },
	{ "mode", required_argument, nullptr, 'm' },
	{ nullptr, 0,                 nullptr, '\0' }

};
struct Line {
	Line(int xc, int yc, int typer, short orginal) : xc(xc), yc(yc), paridx(-1), type(typer), dis(big), isvisit(false), orginal(orginal) {}
	double xc;
	double yc;
	int paridx;
	int type;
	double dis;
	bool isvisit;
	short orginal;

};
bool typematch(Line &pin, Line &chkin) {
	if (pin.type + chkin.type == 20) {
		return false;
	}
	return true;
}
int findlocation(vector<Line> &cooz, int &vertexs) {
	int index = -2;
	double shodis = big;
	for (int i = 1; i < vertexs;++i) {
		if (!(cooz[i].isvisit) && (cooz[i].dis < shodis)) {
			index = i;
			shodis = cooz[i].dis;
		}
	}
	return index;
}
int findlocation(deque<Line> &cooz, int &vertexs) {
	int index = -2;
	double shodis = big;
	for (int i = 1; i < vertexs;++i) {
		if (!(cooz[i].isvisit) && (cooz[i].dis < shodis)) {
			index = i;
			shodis = cooz[i].dis;
		}
	}
	return index;
}
double dist(Line &pin, Line &chkin) {
	return sqrt((pin.xc - chkin.xc)*(pin.xc - chkin.xc) + (pin.yc - chkin.yc)*(pin.yc - chkin.yc));
}
double fasttsp(deque<Line>&coordhold, bool onlyfast) {
	int location = 0;
	double weight = 0;
	vector<int> mytour;
	mytour.reserve(numv);
	//nearest neighbors greedy
	//fuck me you fucking cuck cunt fuck shit i fucking shit can't even. how bout odd? can u du tht?
	//arbitrary insertion 
	mytour.push_back(0);
	double shortestdist = big;
	for (int k = 1; k < numv; ++k) {
		if ((dist(coordhold[0], coordhold[k]) < shortestdist)) {
			double dis = dist(coordhold[0], coordhold[k]);
			shortestdist = dis;
			location = k;

		}
	}
	weight += 2 * shortestdist;
	mytour.push_back(location);
	mytour.push_back(0); // perhaps needs to go to end 
	double d_ik, d_jk, d_ij;
	int best_insertion_loc_so_far;

	for (int k = 1; k < numv; ++k) { // choose the next vertex to insert into the subtour.
		if (!(k == location)) {
			// find the best place in the subtour to add in node k
			// <=> find the two nodes i, j in locs such that...
			// 1) i is next to j in the subtour
			// 2) dist(i,k) + dist(j, k) - dist(i, j) is minimized
			double least_insertion_cost_so_far = big;
			for (int i = 1; i < int(mytour.size() - 1);++i) {
				int j = i + 1;
				d_ik = dist(coordhold[mytour[i]], coordhold[k]);
				d_jk = dist(coordhold[mytour[j]], coordhold[k]);
				d_ij = dist(coordhold[mytour[i]], coordhold[mytour[j]]);
				if ((d_ik + d_jk - d_ij) < least_insertion_cost_so_far) {
					least_insertion_cost_so_far = d_ik + d_jk - d_ij;
					best_insertion_loc_so_far = i; // 
				}
			} // found mimimizing cost
			mytour.insert(mytour.begin() + best_insertion_loc_so_far + 1, k);
			weight = weight + least_insertion_cost_so_far;


		}// closes if skips the one we added above

	}
	if (onlyfast) {
		if (numv == 1) {
			weight = 0;
		}
		cout << weight << '\n';
		for (int o = numv;o > 0; --o) {
			if (o == 0) {
				cout << mytour[o];
			}
			else {
				cout << mytour[o] << " ";
			}
		}
	}
	return weight;

}
double mst(vector<Line> &coordhold, int &vertices) {
	int locationhold = 0;
	coordhold[locationhold].paridx = -2;
	coordhold[locationhold].isvisit = true;
	double weight = 0;
	//intialize parent 
	while (true) {

		coordhold[locationhold].isvisit = true;
		Line parent = coordhold[locationhold];
		for (int j = 0; j < vertices; ++j) {
			Line check = coordhold[j];

			if (!(check.isvisit) && (typematch(parent, check)) && (dist(parent, check) < check.dis)) {
				double dis = dist(parent, check);
				coordhold[j].dis = dis;
				coordhold[j].paridx = locationhold;

			}
		}
		//find new parent
		weight += coordhold[locationhold].dis;
		locationhold = findlocation(coordhold, vertices);
		if (locationhold == -2) {
			break;
		}
	} //close while

	string locs;

	for (int k = 1;k < vertices;++k) {
		ostringstream os;
		if (k < coordhold[k].paridx) {
			os << k << ' ' << coordhold[k].paridx << '\n';
		}
		else {
			os << coordhold[k].paridx << ' ' << k << '\n';
		}
		string s = os.str();
		locs.append(s);
	}
	cout << weight << '\n';
	cout << locs << '\n';

	return weight;
}
double mstonly(deque<Line> &coordhold, int &vertices) {
	int locationhold = 0;
	coordhold[locationhold].paridx = -2;
	coordhold[locationhold].isvisit = true;
	coordhold[locationhold].dis = 0;
	double weight = 0;
	//intialize parent 
	while (true) {

		coordhold[locationhold].isvisit = true;
		Line parent = coordhold[locationhold];
		for (int j = 0; j < vertices; ++j) {
			Line check = coordhold[j];

			if (!(check.isvisit) && (dist(parent, check) < check.dis)) {
				double dis = dist(parent, check);
				coordhold[j].dis = dis;
				coordhold[j].paridx = locationhold;

			}
		}
		//find new parent
		weight += coordhold[locationhold].dis;
		locationhold = findlocation(coordhold, vertices);
		if (locationhold == -2) {
			break;
		}

	} //close while

	for (int q = 0; q < vertices; ++q) {
		coordhold[q].dis = big;
		coordhold[q].paridx = -1;
		coordhold[q].isvisit = false;
	}
	return weight;
}
bool promising(deque<Line> &unused, vector<Line> &path, double &currentdista, double &bestdista) {
	//this is in promosing 
	if (currentdista >= bestdista) {
		return false;
	}
	if (unused.size() < 5) {
		return true;
	}
	////unused.push_back(path.front());
	////unused.push_back(path.back());


	////unused.pop_back();
	////unused.pop_back();

	int sizeunused = int(unused.size());
	double weightfront = big;
	for (int i = 0; i < sizeunused; ++i) {
		double smallnodefront = dist(path.front(), unused[i]);
		if (smallnodefront < weightfront) {
			weightfront = smallnodefront;
		}
	}
	double weightback = big;
	for (int i = 0; i < sizeunused; ++i) {
		double smallnodeback = dist(path.back(), unused[i]);
		if (smallnodeback < weightback) {
			weightback = smallnodeback;
		}
	}
	int vert = int(unused.size());
	double lowerbound = mstonly(unused, vert) + weightback + weightfront + currentdista;
	if (lowerbound >= bestdista) {
		return false;
	}
	return true;

}
void genPerms(vector<Line> &currentpath, deque<Line> &unused,
	double &bestdist, double currentdistance, vector<Line> &finalpath) {
	if (unused.empty()) {
		double comparison = dist(currentpath.back(), currentpath.front());
		if (comparison + currentdistance < bestdist) {
			finalpath = currentpath;
			bestdist = currentdistance + comparison;
		}
		// Do something with the path
		return;
	} // if


	if (!promising(unused, currentpath, currentdistance, bestdist)) {
		return;
	}

	for (unsigned k = 0; k != unused.size(); k++) {
		currentdistance += dist(currentpath.back(), unused.front());
		currentpath.push_back(unused.front());
		unused.pop_front();
		genPerms(currentpath, unused, bestdist, currentdistance, finalpath);

		unused.push_back(currentpath.back());
		currentpath.pop_back();
		currentdistance -= dist(currentpath.back(), unused.back());
	} // for
	return;
} // genPerms()
int main(int argc, char *argv[]) {
	ios_base::sync_with_stdio(false);
	cout << std::setprecision(2); //Always show 2 decimal places
	cout << std::fixed; //Disable scientific notation for large numbers

	int choice;
	int option_index = 0;
	int typepq = 0;
	while ((choice = getopt_long(argc, argv, "hm:", long_options, &option_index)) != -1) {
		switch (choice) {
		case 'm':
			if (optarg[0] == 'M') {
				typepq += 1;

				break;
			}
			else if (optarg[0] == 'F') {
				typepq += 2;

				break;
			}
			else if (optarg[0] == 'O') {
				typepq += 3;

				break;
			}
			else {
				cerr << "Error: invalid mode " << *optarg << '\n';
				exit(1);
			}
		default:
			cerr << "Error: invalid option " << '\n';
			exit(1);
		} // switch
	}

	//int indx = 0;
	int val1, val2, type;
	cin >> numv;
	deque<Line> coorddeq;
	vector<Line> coordvec;
	short indx = 0;
	if (typepq == 1) {
		coordvec.reserve(numv);
		while (cin >> val1 >> val2) {
			if (val1 <= 0 && val2 <= 0) {
				if (val1 == 0 || val2 == 0) {
					type = 2; // you're a doorway
				}
				else {
					type = 15; // you're in the cage
				}
			}
			else {
				type = 5; // you're an okay point
			}
			coordvec.push_back(Line(val1, val2, type,indx));
			++indx;
		}

		coordvec[0].dis = 0;
	}
	else {
		short indx = 0;
		while (cin >> val1 >> val2) {
			if (val1 <= 0 && val2 <= 0) {
				if (val1 == 0 || val2 == 0) {
					type = 2; // you're a doorway
				}
				else {
					type = 15; // you're in the cage
				}
			}
			else {
				type = 5; // you're an okay point
			}
			coorddeq.push_back(Line(val1, val2, type, indx));
			++indx;
		}

		coorddeq[0].dis = 0;
	}
	if (typepq == 1) {
		double hold = mst(coordvec, numv);
		++hold;

	}
	if (typepq == 2) {
		double hold = fasttsp(coorddeq, true);
		++hold;
	}
	if (typepq == 3) {
		double attempt = fasttsp(coorddeq, false);
		vector<Line> currentpath;
		vector<Line> finalpath;
		currentpath.reserve(numv);
		currentpath.reserve(numv);
		currentpath.push_back(coorddeq[0]);
		Line save = coorddeq.front();
		coorddeq.pop_front();
		coorddeq[0].dis = 0;
		double currentdist = 0;

		genPerms(currentpath, coorddeq, attempt, currentdist, finalpath);
		
		if (!finalpath.size()) {
			coorddeq.push_front(save);
			attempt = fasttsp(coorddeq, true);
		}
		else {
			cout << attempt << '\n';
			for (int o = 0;o < numv; ++o) {
				if (o == numv - 1) {
					cout << finalpath[o].orginal;
				}
				else {
					cout << finalpath[o].orginal << " ";
				}
			}
		}
	}
	return 0;
}