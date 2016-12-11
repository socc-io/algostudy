#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

#define INF 0x3FFFFFFF

inline int min(int a, int b)
{
	return a < b ? a : b;
}

int main(void)
{
	for(int p_idx=1;true; ++p_idx)
	{
		int n;
		cin >> n;
		if(n == 0) break;
		int n2 = n*n;
		vector< vector<int> > map(n, vector<int>(n));
		for(int i=0;i<n;++i) {
			for(int j=0;j<n;++j) {
				cin >> map[i][j];
			}
		}
		vector< vector<int> > minCost(n, vector<int>(n, INF));
		vector< vector<int> > S(n, vector<int>(n, 1));
		minCost[0][0] = map[0][0];
		for(int idx=0;idx<n2;++idx) {
			int min_x, min_y;
			int min_val = INF;
			for(int cx=0;cx<n;++cx) {
				for(int cy=0;cy<n;++cy) {
					if(min_val > minCost[cx][cy]) {
						min_val = minCost[cx][cy];
						min_x = cx;
						min_y = cy;
					}
				}
			}
			S[min_x][min_y] = 0;
			if(min_x == n-1 && min_y == n-1) break;
			if(min_x > 0 && S[min_x-1][min_y]) {
				minCost[min_x-1][min_y] = min(minCost[min_x-1][min_y], minCost[min_x][min_y] + map[min_x-1][min_y]);
			}
			if(min_x < n-1 && S[min_x+1][min_y]) {
				minCost[min_x+1][min_y] = min(minCost[min_x+1][min_y], minCost[min_x][min_y] + map[min_x+1][min_y]);
			}
			if(min_y > 0 && S[min_x][min_y-1]) {
				minCost[min_x][min_y-1] = min(minCost[min_x][min_y-1], minCost[min_x][min_y] + map[min_x][min_y-1]);
			}
			if(min_y < n-1 && S[min_x][min_y+1]) {
				minCost[min_x][min_y+1] = min(minCost[min_x][min_y+1], minCost[min_x][min_y] + map[min_x][min_y+1]);
			}
			minCost[min_x][min_y] = INF;
		}
		printf("Problem %d: %d\n", p_idx, minCost[n-1][n-1]);
	}
	return 0;
}