#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define INF 0x7FFFFFFF

int search_case[24][4] = {
	{0, 1, 2, 3}, {0, 1, 3, 2}, {0, 2, 1, 3}, {0, 2, 3, 1}, {0, 3, 1, 2}, {0, 3, 2, 1}, //0
	{1, 0, 2, 3}, {1, 0, 3, 2}, {1, 2, 0, 3}, {1, 2, 3, 0}, {1, 3, 0, 2}, {1, 3, 2, 0}, //1
	{2, 0, 1, 3}, {2, 0, 3, 1}, {2, 1, 0, 3}, {2, 1, 3, 0}, {2, 3, 0, 1}, {2, 3, 1, 0}, // 2
	{3, 0, 1, 2}, {3, 0, 2, 1}, {3, 1, 0, 2}, {3, 1, 2, 0}, {3, 2, 0, 1}, {3, 2, 1, 0}  // 3
};

int m_distance(int x1, int y1, int x2, int y2) {
	return abs(x1 - x2) + abs(y1 - y2);
}

void my_insert(int val, vector<int> &vec)
{
	for(auto it = vec.begin(); it != vec.end(); ++it) {
		if((*it) == val) return;
	}
	vec.push_back(val);
}

int main(int argc, char** argv)
{
	int spot[4][2];
	int maxd = -1;
	int mind = INF;
	vector<int> n_arr;
	for(int i=0;i<4;++i) {
		cin >> spot[i][0] >> spot[i][1];
		my_insert(abs(spot[i][0]), n_arr);
		my_insert(abs(spot[i][1]), n_arr);
	}
	int d[4][4];
	int g_min = INF;
	int g_idx = -1;
	for(auto it = n_arr.begin(); it != n_arr.end(); ++it) {
		int n = (*it);
		for(int i=0;i<4;++i) {
			d[i][0] = m_distance(spot[i][0], spot[i][1],  n,  n);
			d[i][1] = m_distance(spot[i][0], spot[i][1], -n,  n);
			d[i][2] = m_distance(spot[i][0], spot[i][1],  n, -n);
			d[i][3] = m_distance(spot[i][0], spot[i][1], -n, -n);
		}
		int min_dsum = INF;
		for(int i=0;i<24;++i) {
			int* case_set = search_case[i];
			int dsum = d[0][case_set[0]] + d[1][case_set[1]] + d[2][case_set[2]] + d[3][case_set[3]];
			if(min_dsum > dsum) min_dsum = dsum;
		}
		if(g_min > min_dsum) {
			g_min = min_dsum;
			g_idx = n;
		} else if(g_min == min_dsum && n > g_idx) {
			g_idx = n;
		}
	}
	cout << (g_idx << 1);
}