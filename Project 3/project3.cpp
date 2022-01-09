#include <deque>
#include <iostream>
#include <unordered_map>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <functional>
#include <cstdlib>
#include <algorithm>
#include <fstream>

using namespace std;


struct Line {
	Line(long long int time, string cat, string mess, int ent) : time(time), cat(cat), mess(mess), ent(ent) {}
	long long int time;
	string cat;
	string mess; 
	int ent; 
	int ival;
};

struct MasterLog {
	vector<Line> masterlog; 
};


string lower(string in) {
	//string bar;
	transform(in.begin(), in.end(), in.begin(), ::tolower);
	return in;
}

struct sort_tie { 
	bool operator()(const Line &i, const Line &j) const {
		if (i.time == j.time) {
			string icat = lower(i.cat);
			string jcat = lower(j.cat);
			if (icat == jcat) {
				return i.ent < j.ent;
			}
			return icat < jcat;
		}
		return i.time < j.time;
	}
};

struct time_c {
	bool operator()(const Line &i, long long int j) const {
		return i.time < j;
	}
};

struct time_cuper {
	bool operator()( long long int j, const Line &i) const {
		return i.time > j;
	}
};


struct set_inter {
	bool operator()(Line i, string j) const {
		return i.mess > j;
	}
};


int main(int argc, char *argv[]) {
	if (argc) {}
	short flag = 0;
	string in, time, cat, mess, dummy;
	int ent = 0;
	size_t val = 0;
	int valin = 0;
	int temp;
	std::string::size_type sz = 0;
	ifstream file;
	file.open(argv[1], ios::in);
	if (argv[1][0] == '-') {
		cerr << "gibberish";
		exit(0);
	}

	MasterLog Master;
	deque<int> excerpt;
	deque<int> hold;
	deque<int> temphold;
	deque<int> resulthold;
	string one; 
	unordered_map<string, vector<int>> catMap;
	unordered_map<string, vector<int>> keyWordMap;
	
	while (getline(file, in, '|')) {
		string temp;
		temp.reserve(11);
		temp.push_back(in[0]);
		temp.push_back(in[1]);
		temp.push_back(in[3]);
		temp.push_back(in[4]);
		temp.push_back(in[6]);
		temp.push_back(in[7]);
		temp.push_back(in[9]);
		temp.push_back(in[10]);
		temp.push_back(in[12]);
		temp.push_back(in[13]);
		getline(file, cat, '|');
		getline(file, mess);
		//cout << in << ' ' << cat << ' ' << mess << '\n';
		Master.masterlog.emplace_back(Line(stoll(temp, nullptr, 10), cat, mess, ent));



		//this is for timestamp search make an ordered map with timestamp|log entry number
		++ent;
	}
	sort_tie comp;
	time_c compt;
	time_cuper compu;
	sort(Master.masterlog.begin(), Master.masterlog.end(), comp);
	vector<int>appendidx(Master.masterlog.size());
	int fuckme = int(Master.masterlog.size());
	for (int i = 0; i < fuckme; ++i) { //FUCK ME HACKS EVERYWHERE
		appendidx[Master.masterlog[i].ent] = i;
		//this is for category search make a unorderd map with string|i num
		Master.masterlog[i].ival = i;
		string lcat = lower(Master.masterlog[i].cat);
		auto exists = catMap.find(lcat);
		if (exists == catMap.end()) { //if cat doesn't exist and therefore find results end
			vector<int> one(1, i);
			catMap[lcat] = one;
		}
		else {
			catMap[lcat].push_back(i);
		}
		//

		//this is for keyword search make an unordered map with strings of cat & strings of messages|i num
		string allwords = Master.masterlog[i].cat + " " + Master.masterlog[i].mess + " ";
		allwords = lower(allwords);
		auto begc = allwords.begin();
		auto endc = allwords.begin();

		while (!isalnum(*begc)) {
			begc++;
		}
		endc = begc + 1;

		for (; endc != allwords.end(); ++endc) {
			if (!isalnum(*(endc))) {
				string ishere(begc, endc);
				begc = endc + 1;
				auto exists = keyWordMap.find(ishere);
				if (exists == keyWordMap.end()) { //if word doesn't exist and therefore find results end
					vector<int> one(1, i);
					keyWordMap[ishere] = one;
				}
				else if (endc + 1 == allwords.end()) { // this is the last value in the string  
					//string ishere(begc, endc + 1);
					//begc = endc + 1;
					//auto exists = keyWordMap.find(ishere);
					if (exists == keyWordMap.end()) { //if word doesn't exist and therefore find results end
						vector<int> one(1, i);
						keyWordMap[ishere] = one;
					}
					else {
						if (keyWordMap[ishere].back() == i) { continue; }
						keyWordMap[ishere].push_back(i);
					}
				}
				else {
					if (keyWordMap[ishere].back() == i) { continue; }
					keyWordMap[ishere].push_back(i);
				}
			}
		}
	}
	

	std::vector<Line>::iterator lowt, hight;
	

	string tm1, tm2, tmm, cstring, cut;
	std::deque<int>::iterator it;
	auto lowm = Master.masterlog.begin();
	auto highm = Master.masterlog.begin();
	auto cext = catMap.begin();
	auto begc = cut.begin();
	auto endc = cut.begin();
	
	long long int tm1l, tm2l;
	//int val;
	unsigned int q = 0;
	//short count = 0;
	//short lowval, highval;
	vector<string> strwords;
	cout << ent << " entries read" << '\n';
	do {
		char comm;
		cout << "% ";
		cin >> comm;
		switch (comm) {
		case 't':
			flag = 1;
			getline(cin, in);
			if (in.size() != 30) {
				//THIS IS WRONG TIME STAMP TO DO SOMETHING
				cerr << "timestamp incorrectt" << '\n';
				break;
			}
			tm1.reserve(11);
			tm1.push_back(in[1]);
			tm1.push_back(in[2]);
			tm1.push_back(in[4]);
			tm1.push_back(in[5]);
			tm1.push_back(in[7]);
			tm1.push_back(in[8]);
			tm1.push_back(in[10]);
			tm1.push_back(in[11]);
			tm1.push_back(in[13]);
			tm1.push_back(in[14]);
			tm2.reserve(11);
			tm2.push_back(in[16]);
			tm2.push_back(in[17]);
			tm2.push_back(in[19]);
			tm2.push_back(in[20]);
			tm2.push_back(in[22]);
			tm2.push_back(in[23]);
			tm2.push_back(in[25]);
			tm2.push_back(in[26]);
			tm2.push_back(in[28]);
			tm2.push_back(in[29]);
			tm1l = stoll(tm1, nullptr, 10);
			tm2l = stoll(tm2, nullptr, 10);
			tm1.clear(); tm2.clear();
			lowt = lower_bound(Master.masterlog.begin(), Master.masterlog.end(), tm1l, compt);
			hight = upper_bound(lowt, Master.masterlog.end(), tm2l, compu);
			cout << "Timestamps search: " << (hight - lowt) << " entries found" << '\n';
			hold.clear();
			for (; lowt != hight; ++lowt) {
				hold.push_back(lowt->ival);
			}
			break;
		case 'm':
			flag = 1;
			getline(cin, in);
			if (in.size() != 15) {
				//THIS IS WRONG TIME STAMP TO DO SOMETHING
				cerr << "timestamp incorrectm" << '\n';
				break;
			}
			tmm.reserve(11);
			tmm.push_back(in[1]);
			tmm.push_back(in[2]);
			tmm.push_back(in[4]);
			tmm.push_back(in[5]);
			tmm.push_back(in[7]);
			tmm.push_back(in[8]);
			tmm.push_back(in[10]);
			tmm.push_back(in[11]);
			tmm.push_back(in[13]);
			tmm.push_back(in[14]);
			tm2l = stoll(tmm, nullptr, 10);
			tmm.clear();
			lowm = lower_bound(Master.masterlog.begin(), Master.masterlog.end(), tm2l, compt);
			for (highm = lowm; highm!= Master.masterlog.end() && (highm->time == tm2l); highm++) {
			}
			cout << "Timestamp search: " << (highm - lowm) << " entries found" << '\n';
			hold.clear();
			for (; lowm != highm; ++lowm) {
				hold.push_back(lowm->ival);
			}
			break;
		case 'c':
			flag = 1;
			cin.get();
			getline(cin,cstring);
			cstring = lower(cstring);

			cext = catMap.find(cstring);
			if (cext == catMap.end()) { //if cat doesn't exist
				val = 0;
			}
			else {
				val = catMap[cstring].size();
			}
			cout << "Category search: " << val << " entries found" << '\n';
			hold.clear();
			for (unsigned int i = 0; i < val; ++i) {
				hold.push_back(cext->second[i]);
			}
			break;
		case 'k':
			flag = 1;
			getline(cin, cut);
			cut = lower(cut);
			begc = cut.begin();
			while (!isalnum(*begc)) {
				begc++;
			}
			endc = begc + 1;
			if (1) {
				string one(begc, endc);
				if ((one.size() == 1) && endc == cut.end()) {
					strwords.push_back(one);
				}
			}
			for (; endc != cut.end(); ++endc) {
				if (!isalnum(*(endc))) {
					string pushme(begc, endc);
					begc = endc + 1;
					strwords.push_back(pushme);

				}
				else if (endc + 1 == cut.end()) {
					string pushme(begc, endc + 1);
					begc = endc + 1;
					strwords.push_back(pushme);
				}
			}
			for (unsigned int loc = 0; loc < strwords.size(); loc++) {
				cext = keyWordMap.find(strwords[loc]);
				if (cext == keyWordMap.end()) { //if cat doesn't exist
					hold.clear();
					//cout << "Keyword search: " << "0" << " entries found" << '\n';
					break;
				}
				else {
					val = keyWordMap[strwords[loc]].size();
				}
				if (strwords.size() == 1) {
					hold.clear();
					for (unsigned int i = 0; i < val; ++i) {
						hold.push_back(cext->second[i]);
					}
					break;
				}
				if (loc == 0) {
					hold.clear();
					for (unsigned int i = 0; i < val; ++i) {
						hold.push_back(cext->second[i]);
					}
				}
				else {
					temphold.clear();
					for (unsigned int i = 0; i < val; ++i) {
						temphold.push_back(cext->second[i]);
					}
					it = std::set_intersection(hold.begin(), hold.end(), temphold.begin(), temphold.end(), hold.begin());
					hold.resize(it - hold.begin());

				}
			}
			
			strwords.clear();
				cout << "Keyword search: " << hold.size() << " entries found" << '\n';
			break;
		case 'a': // this is hard do later index appending
			cin >> valin;
			if (valin >= int(Master.masterlog.size()) || valin < 0) {
				cerr << "invalidappend" << "\n";
				break;
			}
			excerpt.push_back(appendidx[valin]);
			cout << "log entry " << valin << " appended" << '\n';
			break;
		case 'r':
			if (!flag) {
				cerr << "search did not occur" << '\n';
				break;
			}
			q = 0;
			for (; q < hold.size(); ++q) {
				excerpt.push_back(hold[q]);
			}
			cout <<q<< " log entries appended" << '\n';
			break;
		case 'd':
			cin >> valin;
			if (valin >= int(excerpt.size()) || valin<0) {
				cerr << "invaliddelete" << "\n";
				break;
			}
			excerpt.erase(excerpt.begin() + valin);
			cout << "Deleted excerpt list entry " << valin << "\n";
			break;
		case 'b':
			cin >> valin;
			if (valin >= int(excerpt.size()) || valin < 0) {
				cerr << "invalidmovetobegin" << "\n";
				break;
			}
			temp = excerpt[valin];
			excerpt.erase(excerpt.begin() + valin);
			excerpt.push_front(temp);
			cout << "Moved excerpt list entry " << valin << "\n";
			break;
		case 'e':
			cin >> valin;
			if (valin >= int(excerpt.size()) || valin < 0) {
				cerr << "invalidmovetoend" << "\n";
				break;
			}
			temp = excerpt[valin];
			excerpt.erase(excerpt.begin() + valin);
			excerpt.push_back(temp);
			cout << "Moved excerpt list entry " << valin << "\n";
			break;
		case 's':
			sort(excerpt.begin(), excerpt.end());
			cout << "excerpt list sorted" << '\n';
			break;
		case 'l':
			excerpt.clear();
			cout << "excerpt list cleared" << '\n';
			break;
		case 'g':
			if (!flag) {
				cerr << "search did not occur" << '\n'; 
				break;
			}
			sort(hold.begin(), hold.end());
			for (unsigned int i = 0; i < hold.size(); ++i) {
				Line entry = Master.masterlog[hold[i]];
				string num = to_string(entry.time);
				//int big = num.size();
				int location=0;
				cout << entry.ent << "|"; //75:12:52:07:49
				//for (int z = 0; z < 10; z++) {
					if (num.size() != 10) {
						for (unsigned int r = 0; r < 10 - num.size(); r++, location++) {
							cout << "0";
							if (r % 2) {
								cout << ":";
							}
						}
					}
					for (unsigned int l = 0; l < num.size(); l++, location++) {
						cout << num[l];
						if (location % 2 && (location != 9)) {
							cout << ":";
						}
					}
				//}
				cout << "|" << entry.cat << "|" << entry.mess << "\n";

			}
			break;
		case 'p':
			for (unsigned int i = 0; i < excerpt.size(); ++i) {
				Line entry = Master.masterlog[excerpt[i]];
				string num = to_string(entry.time);
				//int big = num.size();
				int location = 0;
				cout << i << "|" << entry.ent << "|"; //75:12:52:07:49
										  //for (int z = 0; z < 10; z++) {
				if (num.size() != 10) {
					for (unsigned int r = 0; r < 10 - num.size(); r++, location++) {
						cout << "0";
						if (r % 2) {
							cout << ":";
						}
					}
				}
				for (unsigned int l = 0; l < num.size(); l++, location++) {
					cout << num[l];
					if (location % 2 && (location != 9)) {
						cout << ":";
					}
				}
				//}
				cout << "|" << entry.cat << "|" << entry.mess << "\n";

			}
			break;
		case 'q':
			return 0;
		case '#':
			getline(cin, dummy);
			continue;
		default:
			cerr << "invalid option " << '\n';

			break;
		} // switch
	} //dp
	while (true);
	
}