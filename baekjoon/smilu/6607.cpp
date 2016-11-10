#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstdio>

using namespace std;

#define INF 9999999

const int jump[8][2] = {
	{-2, -1},
	{-2, 1},
	{-1, -2},
	{1, -2},
	{-1, 2},
	{1, 2},
	{2, -1},
	{2, 1}
};

bool DO()
{
	pair<int, int> size;
	pair<int, int> first_pos;
	pair<int, int> leaf;
	int res = -1;
	if(cin >> size.first >> size.second >> first_pos.first >> first_pos.second >> leaf.first >> leaf.second) {
		--first_pos.first; --first_pos.second; --leaf.first; --leaf.second;
		vector< vector<int> > map(size.first, vector<int>(size.second, INF));
		queue< pair<int, int> > Q;
		map[first_pos.first][first_pos.second] = 0;
		Q.push(first_pos);
		while(!(Q.empty())) {
			pair<int, int> front = Q.front();
			Q.pop();
			if(front == leaf) {
				res = map[front.first][front.second];
				break;
			}
			int next_val = map[front.first][front.second] + 1;
			for(int i=0;i<8;++i) {
				pair<int, int> next(front.first + jump[i][0], front.second + jump[i][1]);
				if(!(0 <= next.first && next.first < size.first && 0 <= next.second && next.second < size.second)) {
					continue;
				}
				if(next_val < map[next.first][next.second]) {
					map[next.first][next.second] = next_val;
					Q.push(next);
				}
			}
		}
		if(res == -1) cout << "impossible" << endl;
		else cout << res << endl;
		return false;
	}
	else {
		return true;
	}
}

int main(int argc, char** argv)
{
	for(;;) {
		if(DO()) break;
	}
	return 0;
}