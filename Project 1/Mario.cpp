#include <deque>
#include <iostream>
#include <getopt.h>
#include <string>
#include <deque>
#include <vector>
#include <sstream>
#include <cstdlib>


//ios_base::sync_with_stdio(false);
using namespace std;

struct Square {
	char read;
	char pred; 
	Square() : read('.'), pred('o') {}
};

int mkint(char integer) {
	return integer - '0';
}

void isvalid(char input) {
	if (input == '.' || input == 'S' || input == 'C' || input == '#' || input == '!' ||
		input == '0' || input == '1' || input == '2' || input == '3' || input == '4' ||
		input == '5' || input == '6' || input == '7' || input == '8' || input == '9') {
		return;
	}
	else {
		//if error print to cerr and exit(1)
		cerr << "Invalid Character ";
		exit(0);
	}
}

void backwards(vector<vector<Square>> &castlein, int mvpin, int rmin, int &dimin, int &choi, int &nmroom) {
	char val;
	cout << dimin << '\n';
	cout << nmroom << '\n';
	if (choi == 7 || choi == 11) {

		while (castlein[rmin][mvpin].pred != '<') {
			val = castlein[rmin][mvpin].pred;
			if (val == 'n') {
				castlein[rmin][mvpin + dimin].read = 'n';

				mvpin = mvpin + dimin;
			}
			else if (val == 'e') {
				castlein[rmin][mvpin - 1].read = 'e';

				mvpin = mvpin - 1;
			}
			else if (val == 's') {
				castlein[rmin][mvpin - dimin].read = 's';

				mvpin = mvpin - dimin;
			}
			else if (val == 'w') {
				castlein[rmin][mvpin + 1].read = 'w';

				mvpin = mvpin + 1;
			}
			else if (isdigit(val)) {
				castlein[mkint(val)][mvpin].read = 'p';
				rmin = mkint(val);
			}
		}
		for (int rm = 0; rm < nmroom; ++rm) { // print the castle 
			cout << "//castle room " << rm << '\n';
			for (int col = 0; col < dimin*dimin;++col) {
				if (!(col%dimin) && col != 0) {
					cout << '\n' << castlein[rm][col].read;
				}
				else if (col == (dimin*dimin) - 1) {
					cout << castlein[rm][col].read << '\n';
				}
				else {
					cout << castlein[rm][col].read;
				}
			}

		}
	} //map output
	else {
		cout << "//path taken" << '\n';
		vector<string> locs;
		int row;
		while (castlein[rmin][mvpin].pred != '<') {
			val = castlein[rmin][mvpin].pred;
			if (val == 'n') {
				row = (mvpin + dimin) / dimin;
				ostringstream os;
				os << '(' << rmin << ',' << row << ',' << (mvpin + dimin) - row*dimin << ',' << 'n' << ')' << '\n';
				string s = os.str();
				locs.push_back(s);
				mvpin = mvpin + dimin;
			}
			else if (val == 'e') {
				row = (mvpin - 1) / dimin;
				ostringstream os;
				os << '(' << rmin << ',' << row << ',' << (mvpin - 1) - row*dimin << ',' << 'e' << ')' << '\n';
				string s = os.str();
				locs.push_back(s);
				mvpin = mvpin - 1;
			}
			else if (val == 's') {
				row = (mvpin - dimin) / dimin;
				ostringstream os;
				os << '(' << rmin << ',' << row << ',' << (mvpin - dimin) - row*dimin << ',' << 's' << ')' << '\n';
				string s = os.str();
				locs.push_back(s);
				mvpin = mvpin - dimin;
			}
			else if (val == 'w') {
				row = (mvpin + 1) / dimin;
				ostringstream os;
				os << '(' << rmin << ',' << row << ',' << (mvpin + 1) - row*dimin << ',' << 'w' << ')' << '\n';
				string s = os.str();
				locs.push_back(s);
				mvpin = mvpin + 1;
			}
			else if (isdigit(val)) {
				row = (mvpin) / dimin;
				ostringstream os;
				os << '(' << val << ',' << row << ',' << (mvpin)-row*dimin << ',' << 'p' << ')' << '\n';
				string s = os.str();
				locs.push_back(s);
				rmin = mkint(val);
			}
		}
		for (std::size_t i = 0; i != locs.size(); ++i)
		{
			std::cout << locs[locs.size() - i - 1];
		}
	} //list output
}
	

bool canwalk(Square pos) {
	if (pos.pred != 'o' || pos.read == '#' || pos.read == '!') { //if you haven't been discoverd or are a wall or minion
		return false;
	}
	else {
		return true;
	}
}



static struct option long_options[]{
	{ "stack", no_argument, nullptr, 's' },
	{ "queue", no_argument,       nullptr, 'q' },
	{ "output", required_argument, nullptr, 'o' },
	{ "help", no_argument,       nullptr, 'h' },
	{ nullptr, 0,                 nullptr, '\0' }
	
};

int main(int argc, char *argv[]) {
	int choice;
	int choi = 0;
	int option_index = 0;
	// TODO: Fill in the double quotes, to match the mode and help options.
	while ((choice = getopt_long(argc, argv, "sqo:h", long_options, &option_index)) != -1) {
		//0 -> stack Map (7)
		//1 -> stack list (9)
		//2 -> queue map (11)
		//3 -> queue list (13)
		switch (choice) {
		case 'o':
			if (*optarg != 'M' && *optarg != 'L') {
				cerr << "Error: invalid mode " << *optarg << '\n';
				exit(1);
			} // if
			else if (*optarg == 'M') {
				choi += 5;
			}
			else if (*optarg == 'L') {
				choi += 7;
			}
			break;

		case 's':
			choi += 2;
			break;
		case 'q':
			choi += 6;
			break;
		case 'h':
			cerr << "You requested help. I have none to give." << '\n';
			exit(1);
		default:
			cerr << "Error: invalid option " << '\n';
			exit(1);
		} // switch
	}// while
	if ((choi == 7) || (choi == 9) || (choi == 11) || (choi == 13)) { // fix

	}
	else {
		cerr << "Error: Too many or too few options " << '\n';
		exit(1);
	}
	//getopt 
	char mode;
	int dim, nrm, mvrm, mvp, tmvrm, tmvmp;
	mvp = -1; 
	mvrm = -1;
	char arr[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
	string in;
	//input file 
	cin >> mode;
	cin >> dim;
	cin >> nrm;
	Square intSquare;
	vector<vector<Square>> castle(nrm, vector<Square>(dim*dim, intSquare));
	if (mode == 'M') {
		//initialize castle as a 2D array cache it in a sense that it's castle[room][dim*row+col]	 
		for (int rm = 0; rm < nrm; ++rm) { // populate the castle with all values (srt will serve as room)
			for (int row = 0; row < dim;) { // iterate through how many rows we have 
				getline(cin, in);
				if (in[0] == '/' || in.empty())
					continue;
				for (int col = 0; col < dim; ++col) { // iterate through the string 
					isvalid(in[col]);
					if (in[col] == 'S') { //if start value
						mvrm = rm;
						mvp = row*dim + col;
					}
					castle[rm][row*dim + col].read = in[col];
				}
				++row;
			}
		}
	}
	else {
		long unsigned int id2, id3;

		while (getline(cin, in)) {
			if (in[0] == '/' || in.empty())
				continue;
			string sbstr1 = in.substr(3, in.size() - 1);
			id2 = sbstr1.find(',');
			string r1w = (sbstr1.substr(0, id2));

			string sbstr2 = sbstr1.substr(id2+1, sbstr1.size() - 1);
			id3 = sbstr2.find(',');
			string c1w = (sbstr2.substr(0, id3));

			char token = in[in.size() - 2];
			isvalid(token);
			int rm = mkint(in[1]); 
			int rw = atoi(r1w.c_str());
			int col = atoi(c1w.c_str()); 
			int pos = rw*dim + col;
			if (rm >= 0 && rm <= nrm - 1 && pos >= 0 && pos < dim*dim) {
				castle[rm][pos].read = token;
				if (token == 'S') { //if start value
					mvrm = rm;
					mvp = pos;
				}
			}
			else {
				//if error print to cerr and exit(1)
				cerr << "Invalid Character ";
				exit(0);
			}
		}

	}

	deque <pair<int, int>> contain; //first is room, second is ent
	castle[mvrm][mvp].pred = '<'; //give start a special character
	contain.push_back(make_pair(mvrm, mvp));  //add start to container

	while (!contain.empty()) {

		if (choi == 7 || choi == 9) { //stack
			mvrm = contain.back().first;
			mvp = contain.back().second;
			contain.pop_back(); //pop is the first thing 
		}
		else { //queue
			mvrm = contain.front().first;
			mvp = contain.front().second;
			contain.pop_front();
		}

		if (isdigit(castle[mvrm][mvp].read)) { //if this is a pipe do things

			tmvrm = mkint(castle[mvrm][mvp].read);
			tmvmp = mvp;
			if (tmvrm <= nrm - 1 && canwalk(castle[tmvrm][tmvmp])) { //if you're a valid room and pipe leads to NOT a min, wall, or discovered thing
				castle[tmvrm][tmvmp].pred = arr[mvrm];
				if (castle[tmvrm][tmvmp].read == 'C')
				{
					backwards(castle, tmvrm, tmvmp, dim, choi, nrm);
					return 0;
				}
				contain.push_back(make_pair(tmvrm, mvp));
			}
		}

		//if you're invalid just don't add it 

		else {

			if ((mvp - dim > -1) && canwalk(castle[mvrm][mvp - dim])) { //if you're higher than -1 and can walk
				castle[mvrm][mvp - dim].pred = 'n';
				if (castle[mvrm][mvp - dim].read == 'C')
				{
					backwards(castle, mvp - dim, mvrm, dim, choi, nrm);
					return 0;
				}
				contain.push_back(make_pair(mvrm, mvp - dim));  //go North 
			}

			if ((mvp + 1) % dim && (mvp + 1 < dim*dim) && canwalk(castle[mvrm][mvp + 1])) { // math
				castle[mvrm][mvp + 1].pred = 'e';
				if (castle[mvrm][mvp + 1].read == 'C')
				{
					backwards(castle, mvp + 1, mvrm, dim, choi, nrm);
					return 0;
				}
				contain.push_back(make_pair(mvrm, mvp + 1)); //go EAST 
			}

			if ((mvp + dim < dim*dim) && canwalk(castle[mvrm][mvp + dim])) { //math
				castle[mvrm][mvp + dim].pred = 's';
				if (castle[mvrm][mvp + dim].read == 'C')
				{
					backwards(castle, mvp + dim, mvrm, dim, choi, nrm);
					return 0;
				}
				contain.push_back(make_pair(mvrm, mvp + dim));
			}

			if (mvp % dim && (mvp - 1 > -1) && canwalk(castle[mvrm][mvp - 1])) { //math
				castle[mvrm][mvp - 1].pred = 'w';
				if (castle[mvrm][mvp - 1].read == 'C')
				{
					backwards(castle, mvp - 1, mvrm, dim, choi, nrm);
					return 0;
				}
				contain.push_back(make_pair(mvrm, mvp - 1));//go WEST

			}
		}
	}

	cout << "no solution"; 
	return 0; 
}