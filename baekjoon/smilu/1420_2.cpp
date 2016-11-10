#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define CONST_NEXT_SIZE 4

struct path {
	vector< pair<int, int> > nexts;
};

void setReachable(pair<int, int> pos, vector< vector<int> > &r, vector< vector<path> > &paths)
{
	if(r[pos.first][pos.second] == 1) return;
	r[pos.first][pos.second] = 1;
	vector< pair<int, int> > &my_nexts = paths[pos.first][pos.second].nexts;
	for(vector< pair<int, int> >::iterator it = my_nexts.begin(); it != my_nexts.end(); ++it) {
		setReachable(*it, r, paths);
	}
}

bool find_augmenting(vector< pair<int, int> > &augmenting, vector< vector<path> > &paths, pair<int, int> pos, pair<int, int> &e)
{
	augmenting.push_back(pos);
	if(pos == e) {
		return true;
	}
	vector< pair<int, int> > &my_nexts = paths[pos.first][pos.second].nexts;
	for(vector< pair<int, int> >::iterator it = my_nexts.begin(); it != my_nexts.end(); ++it) {
		if(find(augmenting.begin(), augmenting.end(), *it) != augmenting.end()) continue;
		if(find_augmenting(augmenting, paths, *it, e)) {
			return true;
		}
	}
	augmenting.pop_back();
	return false;
}

int main(int argc, char** argv)
{
	int xsize, ysize;
	cin >> xsize >> ysize;
	pair<int, int> const_next[CONST_NEXT_SIZE] = {pair<int, int>(1, 0), pair<int, int>(-1, 0), pair<int, int>(0, 1), pair<int, int>(0, -1)};
	vector< vector<int> > map(xsize, vector<int>(ysize, 0));
	vector< vector<path> > paths(xsize, vector<path>(ysize));
	pair<int, int> start_point;
	pair<int, int> end_point;
	string line_tmp;
	for(int i=0;i<xsize;++i) {
		cin >> line_tmp;
		for(int j=0;j<ysize;++j) {
			map[i][j] = (int)line_tmp[j];
			if(line_tmp[j] == 'K') {
				start_point.first = i;
				start_point.second = j;
			}
			else if(line_tmp[j] == 'H') {
				end_point.first = i;
				end_point.second = j;
			}
		}
	}
	// cout << "INPUT COMPLETE" << endl;
	if(abs(end_point.first - start_point.first) + abs(end_point.second - start_point.second) == 1) {
		cout << -1 << endl;
		return 0;
	}
	// cout << "Adjacent Check COMPLETE" << endl;
	for(int i=0;i<xsize;++i) {
		for(int j=0;j<ysize;++j) {
			if(map[i][j] == '#') continue;
			pair<int, int> next;
			for(int k=0;k<CONST_NEXT_SIZE;++k) {
				next.first = i + const_next[k].first;
				next.second = j + const_next[k].second;
				if(next.first >= 0 && next.first < xsize &&
					next.second >= 0 && next.second < ysize &&
					map[next.first][next.second] != '#') {
					paths[i][j].nexts.push_back(next);
				}
			}
		}
	}
	// cout << "PATH Building COMPLETE" << endl;
	vector< vector<path> > origin_path = paths;
	vector< pair<int, int> > augmenting;
	while(find_augmenting(augmenting, paths, start_point, end_point)) {
		for(int i=1;i<augmenting.size();++i) {
			vector< pair<int, int> > &tmp_nexts = paths[augmenting[i-1].first][augmenting[i-1].second].nexts;
			tmp_nexts.erase(find(tmp_nexts.begin(), tmp_nexts.end(), augmenting[i]));
			paths[augmenting[i].first][augmenting[i].second].nexts.push_back(augmenting[i-1]);
		}
		augmenting.clear();
	}
	// cout << "Ford Fulkerson COMPLETE" << endl;
	vector< vector<int> > reachable(xsize, vector<int>(ysize, 0));
	setReachable(start_point, reachable, paths);
	// cout << "Finding Reachable COMPLETE" << endl;
	vector< pair<int, int> > toBlock;
	int cnt_block = 0;
	for(int i=0;i<xsize;++i) {
		for(int j=0;j<ysize;++j) {
			if(reachable[i][j] == 0) continue;
			for(vector< pair<int, int> >::iterator it = origin_path[i][j].nexts.begin(); it != origin_path[i][j].nexts.end(); ++it) {
				if(reachable[(*it).first][(*it).second] == 0) {
					++cnt_block;
				}
			}
		}
	}
	// cout << "Counting Cut COMPLETE" << endl;
	// cout << "Result: ";
	cout << cnt_block << endl;
	return 0;
}