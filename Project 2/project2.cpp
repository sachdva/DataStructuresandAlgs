#include <deque>
#include <iostream>
#include <getopt.h>
#include <string>
#include <deque>
#include <vector>
#include <sstream>
#include <functional>
#include <cstdlib>
#include "JarJarPQ.h"
#include "SortedPQ.h"
#include "BinaryPQ.h"
#include "PairingPQ.h"
#include "P2.h"



using namespace std;
int big = std::numeric_limits<int>::max(); 
int pq = 0;
struct Line {
	int time;
	int gen;
	int plnt;
	int fs;
	int ntrp;
	int readord; 

};

struct General {
	int nJ; 
	int nS; 
	int die; //aka me
};

struct MovieW {
	MovieW() : atkS(0, -1), atkJ(big, -1), ambS(0, -1), ambJ(big,-1), ptS(0,-1),ptJ(big,-1){}
	//pair will be Force Sensitivity, timestamp
	pair<int, int> atkS; // this will be the most recent Highest Force Sith 
	pair<int, int> atkJ; //this will be the oldest low F Jed  
	pair<int, int> ambS; //this will be the oldest high F Sith
	pair<int, int> ambJ; // this will be the most recent low F Jedi
	pair<int, int> ptS; // this will be the most recent high F Sith
	pair<int, int> ptJ; // this will be the most recent high F Sith
};

struct SithCompare {
	bool operator()(const Line &left,
		const Line &right) const {
		if (left.fs == right.fs) { 
			return left.readord > right.readord;
		}
		else {
			return left.fs < right.fs;
		}

	}
	bool operator()(const Line *left,
		const Line *right) const {
		if (left->fs == right->fs) { // 
			return left->readord > right->readord;
		}
		else {
			return left->fs < right->fs;
		}

	}
};
struct JediCompare {
	bool operator()(const Line &left,
		const Line &right) const {
		if (left.fs == right.fs) { // 
			return left.readord > right.readord;
		}
		else {
			return left.fs > right.fs; 
		}
		
	}
	bool operator()(const Line *left,
		const Line *right) const {
		if (left->fs == right->fs) { // 
			return left->readord > right->readord;
		}
		else {
			return left->fs > right->fs;
		}

	}
};

struct Planet {
	Eecs281PQ<Line, SithCompare> *Sith;
	Eecs281PQ<Line, JediCompare> *Jedi;
};

template<typename Comparison>
Eecs281PQ<Line, Comparison> * PQfac(int &pq, Comparison C) {

	if (pq == 0)
		return new JarJarPQ<Line, Comparison>(C);
	else if (pq == 2) // Binary
		return new BinaryPQ<Line, Comparison>(C);
	else if (pq == 1 ) // Sorted
		return new SortedPQ<Line, Comparison>(C);
	else if (pq == 3 ) // Pairing
		return new PairingPQ<Line, Comparison>(C);
	else
		return new JarJarPQ<Line, Comparison>(C); //default case
}

static struct option long_options[]{
	{ "verbose", no_argument, nullptr, 'v' },
	{ "median", no_argument,       nullptr, 'm' },
	{ "general-eval", no_argument, nullptr, 'g' },
	{ "watcher", no_argument,       nullptr, 'w' },
	{ "queue", required_argument, nullptr, 'q' },
	{ nullptr, 0,                 nullptr, '\0' }

};

struct Median {
	Eecs281PQ<int, greater<int>> *higher;
	Eecs281PQ<int, less<int>> *lesser;
	//JarJarPQ< int, greater<int> > higher;	// it it's higher than median smaller is topmost 
	//JarJarPQ< int, less<int> > lesser; 	//if it's less than the median add here so greater is on top
	 
	Median() {
		if (pq == 0) {
			 higher = new JarJarPQ<int, greater<int>>;
			 lesser = new JarJarPQ<int, less<int>>;
		}
		else if (pq == 2) {// Binary
			 higher = new BinaryPQ<int, greater<int>>;
			 lesser = new BinaryPQ<int, less<int>>;
		}
		else if (pq == 1) { // Sorted
			 higher = new SortedPQ<int, greater<int>>;
			lesser = new SortedPQ<int, less<int>>;
		}
		else if (pq == 3) { // Pairing
			 higher = new PairingPQ<int, greater<int>>;
			 lesser = new PairingPQ<int, less<int>>;
		}
		else {
			 higher = new JarJarPQ<int, greater<int>>;
			 lesser = new JarJarPQ<int, less<int>>;
		}
	
		higher->push(big);
		lesser->push(0); //min
		size = 0;
	}
	int size;
	void push(int item) {

		if (item >= higher->top()) { 
			//if greater than push to higher PQ
			higher->push(item);
		}
		else { 
			//or push to lower pQ
			lesser->push(item);
		}

		bool uhigher = (higher->size() - lesser->size() == 2);
		bool lhigher = (lesser->size() - higher->size() == 2);

		if (uhigher){
			lesser->push(higher->top());        
			higher->pop();                    
		}

		else if (lhigher) {
			higher->push(lesser->top());               
			lesser->pop();                          
		}
		++size; 
	}

	int medval() {
		if (higher->size() > lesser->size()) {
			return higher->top();
		}

		else if (lesser->size() > higher->size()) {
			return lesser->top();
		}
		else {
			return((higher->top() + lesser->top()) / 2);
		}
	}
};


int main(int argc, char *argv[]) {
	ios_base::sync_with_stdio(false);
	int choice;
	int typepq = 0;
	int bw = 0; 
	int bg = 0;
	int bm= 0;
	int bv = 0; 
	int option_index = 0; 
	int battle = 0;
	int trpleft; 
	// TODO: Fill in the double quotes, to match the mode and help options.
	while ((choice = getopt_long(argc, argv, "vmgwq:", long_options, &option_index)) != -1) {
		switch (choice) {
		case 'q':
				if (optarg[0] == 'S') {
				typepq += 1;
				
				break;
			}
			else if (optarg[0] == 'B') {
				typepq += 2;
				
				break;
			}
			else if (optarg[0] == 'P') {
				typepq += 3;
				
				break;
			}
			else if (optarg[0] == 'J') {
				break;
			}
			else {
				cerr << "Error: invalid mode " << *optarg << '\n';
				exit(1);
			}
		case 'w':
			bw += 1;
			break;
		case 'g':
			bg += 1;
			break;
		case 'm':
			bm += 1;
			break;
		case 'v':
			bv += 1;
			break;
		default:
			cerr << "Error: invalid option " << '\n';
			exit(1);
		} // switch
	}


	string dummyLine, mode, side; 
	int timein, numgen, numplan, gen, plan, fs, trp, seed, numdep, rate;
	int trplst = 0;
	char dummy; 
	int rval = 0;
	int pr = 0;
	int orgtime = 0; 
	getline(cin, dummyLine);
	cin >> dummyLine; 
	cin >> mode; 
	cin >> dummyLine; 
	cin >> numgen; 
	cin >> dummyLine;
	cin >> numplan; 
	stringstream ss;
	if (mode == "PR") {
		pr += 1; 
		cin >> dummyLine;
		cin >> seed;
		cin >> dummyLine;
		cin >> numdep;
		cin >> dummyLine;
		cin >> rate;
		P2::PR_init(ss, seed, numgen, numplan, numdep,
			rate);
	}
	// If prMode is on, read from the stringstream. Otherwise, use cin.
	istream &inputStream = pr ? ss : cin;

		vector<Planet> planets(numplan);
		vector<General> generals(numgen);
		vector<MovieW> movie(numplan);
		vector<Median> medianshite(numplan); 

		SithCompare S;
		JediCompare J;
		//Eecs281PQ<Line*, SithCompare> *Sith = PQfac(typepq, S);
		//Eecs281PQ<Line*, JediCompare> *Jedi = PQfac(typepq, J);
		//make a vector of planets that hold pQs
		//vector of a struct of a planet that holds two pQs, one for Jedi, one for Sith
		//the PQs will be ordered in highest FS for SITH
		//lowerer FS for JEDI
		for (int i = 0; i < numplan; ++i) {
			planets[i].Jedi = PQfac(typepq, J);
			planets[i].Sith = PQfac(typepq, S);
		}
		cout << "Deploying troops..." << '\n'; 
		while (inputStream >> timein >> side >> dummy >> gen >> dummy >> plan >>
			dummy >> fs >> dummy >> trp) {

			if (timein < 0 || gen < 0 || gen >= numgen || plan < 0 || plan >= numplan ||
				fs <= 0 || trp <= 0 || timein < orgtime) {
				cerr << "Input Error" << '\n';
				exit(1);
			}
			++rval;
			Line line = { timein, gen, plan, fs, trp, rval };
			
			if (bg) {
				if (side == "SITH") {
					generals[gen].nS += trp;
				}
				else { //side == "Jedi"
					generals[gen].nJ += trp;
				}
			}

			if (bw) {
				//attack
				if (side == "SITH") {
					if (movie[plan].ptJ.second == -1) {
						
					}
					else {
						if (fs >= movie[plan].ptJ.first && ((fs - movie[plan].ptJ.first)> (movie[plan].atkS.first - movie[plan].atkJ.first) )) {
							movie[plan].atkS.first = fs;
							movie[plan].atkS.second = timein;
							movie[plan].atkJ.first = movie[plan].ptJ.first;
							movie[plan].atkJ.second = movie[plan].ptJ.second;
						}
					}
				}
				else { //side ==JEDI
					if (fs < movie[plan].ptJ.first) {
						movie[plan].ptJ.first = fs;
						movie[plan].ptJ.second = timein;

					}
				}



				//ambush
				if (side == "JEDI") {
					if (movie[plan].ptS.second == -1) {
						
					}
					else {
						if (fs <= movie[plan].ptS.first && (( movie[plan].ptS.first - fs) > (movie[plan].ambS.first- movie[plan].ambJ.first))) {
							movie[plan].ambJ.first = fs;
							movie[plan].ambJ.second = timein;
							movie[plan].ambS.first = movie[plan].ptS.first;
							movie[plan].ambS.second = movie[plan].ptS.second;
						}
					}
				}
				else { //side ==Sith
					if (fs > movie[plan].ptS.first) {
						movie[plan].ptS.first = fs;
						movie[plan].ptS.second = timein;

					}
				}
			}

			if (bm) { //if median
				if (timein != orgtime) { // if we have a new timestamp and medianshite isn't empty 
					for (int i = 0; i < numplan; ++i) {  // cout for all plan
						if (medianshite[i].size) {
							cout << "Median troops lost on planet " << i << " at time " << orgtime << " is " << medianshite[i].medval() << '.' << '\n';
						}
					}
				}
			}
			orgtime = timein;
			if (side == "JEDI") {
				planets[plan].Jedi->push(line);
			}
			if (side == "SITH") {
				planets[plan].Sith->push(line);
			}
			if (planets[plan].Jedi->empty() || planets[plan].Sith->empty()) {
				orgtime = timein;
				continue;
			}
			else if (planets[plan].Sith->top().fs < planets[plan].Jedi->top().fs) {
				orgtime = timein;
				continue;
			}
			while (planets[plan].Sith->top().fs >= planets[plan].Jedi->top().fs) { //while an attack could happen in a specific planets PQ -- Jedifs>Sithfs
				++battle;
				bool Sithhigher = planets[plan].Sith->top().ntrp > planets[plan].Jedi->top().ntrp; // FS is not equal Sith have higher -- if Sith have higher num troops
				bool Jedihigher = planets[plan].Sith->top().ntrp < planets[plan].Jedi->top().ntrp; // FS is not equal Sith have higher -- if Jedi have higher num troops
				bool equal = planets[plan].Sith->top().ntrp == planets[plan].Jedi->top().ntrp; // FS is not equal Sith have higher -- if Jedi have higher num troops
				if (Sithhigher || Jedihigher || equal) {
					int sithgen = planets[plan].Sith->top().gen;
					int jedigen = planets[plan].Jedi->top().gen;
					int sithtrp = planets[plan].Sith->top().ntrp;
					int jeditrp = planets[plan].Jedi->top().ntrp;

					//make a temp node to save the trpleft and store trplst
					if (Sithhigher) {
						trpleft = sithtrp - jeditrp;
						trplst = jeditrp * 2;
						Line temp = planets[plan].Sith->top();
						temp.ntrp = trpleft;
						planets[plan].Sith->pop();
						planets[plan].Sith->push(temp);
						planets[plan].Jedi->pop(); //killed Jedi

					}
					if (Jedihigher) {
						trpleft = jeditrp - sithtrp;
						trplst = sithtrp * 2;
						Line temp = planets[plan].Jedi->top();
						temp.ntrp = trpleft;
						planets[plan].Jedi->pop();
						planets[plan].Jedi->push(temp);
						planets[plan].Sith->pop(); //killed Sith
					}
					if (equal) {
						trplst = sithtrp * 2;
						planets[plan].Jedi->pop(); //killed themselves
						planets[plan].Sith->pop(); //killed themselves
					}


					if (bm) { //if median
						if (timein != orgtime) { // if we have a new timestamp and medianshite isn't empty 
							for (int i = 0; i < numplan; ++i) {  // cout for all plan
								if (medianshite[i].size) {
									cout << "Median troops lost on planet " << i << " at time " << orgtime << " is " << medianshite[i].medval() << '.' << '\n';
								}
							}
							medianshite[plan].push(trplst);
						}
						else {
							medianshite[plan].push(trplst);
						}
					}
					orgtime = timein;
					if (bv) {
						cout << "General " << sithgen << "'s" << " battalion attacked General " << jedigen <<
							"'s battalion on planet " << plan << ". " << trplst << " troops were lost." << "\n";
						//cout << battle << "\n"; 
					}
					if (bg) {
						generals[sithgen].die += trplst / 2;
						generals[jedigen].die += trplst / 2;
					}

					if (planets[plan].Jedi->empty() || planets[plan].Sith->empty()) {
						break; //take in a new line get out of this while loop
					}
				} // if Sith Higher or Jedihigher
				
				//cout << battle << '\n';
			}///while you're attacking
			//orgtime = timein;
		}//for all lines
		if (bm) { //if median
			for (int i = 0; i < numplan; ++i) {  // cout for all plan
				if (medianshite[i].size) {
					cout << "Median troops lost on planet " << i << " at time " << orgtime << " is " << medianshite[i].medval() << '.' << '\n';
					//medianshite[i].popall(); 
				}
			}
			
		}

		cout << "---End of Day---" << '\n' << "Battles: " << battle << '\n';
		
		if (bg) {
			cout << "---General Evaluation---" << '\n'; 
			for (int i = 0; i < numgen; ++i) {
				int tot = generals[i].nS + generals[i].nJ; 
				cout << "General " << i << " deployed " << generals[i].nJ << " Jedi troops and " << generals[i].nS << " Sith troops, and " <<
					tot-generals[i].die << '/' << tot << " troops survived." << "\n";
			}
		}

		if (bw) {
			cout << "---Movie Watcher---" << '\n';
			for (int i = 0; i < numplan; ++i) {
				cout << "A movie watcher would enjoy an ambush on planet " << i << " with Sith at time " << movie[i].ambS.second <<
					" and Jedi at time " << movie[i].ambJ.second << "." << "\n"; 
				cout << "A movie watcher would enjoy an attack on planet " << i << " with Jedi at time " << movie[i].atkJ.second <<
					" and Sith at time " << movie[i].atkS.second << "." << "\n";
			}
		}
		for (int i = 0; i < numplan;++i) {
			delete planets[i].Jedi; 
			delete planets[i].Sith;
			delete medianshite[i].higher; 
			delete medianshite[i].lesser;
		}
		return 0;
	}  
	


	