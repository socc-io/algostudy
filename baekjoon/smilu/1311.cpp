/**
 * @author: smilu97
 * @created: 2021-11-03
 * problem: https://www.acmicpc.net/problem/1311
 */

#include <bits/stdc++.h>
using namespace std;

int n;
int cost[21][21];
int dp[20][1<<20];

/**
 * @arg x the index of worker
 * @arg vf the flag for which works are done
 */
int getdp(int x, int vf) {
	if (x >= n) return 0;
	int &ret = dp[x][vf];
	if (~ret) return ret;
	ret = 0x3f3f3f3f;
	for (int i = 0; i < n; i++) {
		if (vf & (1<<i)) continue;
		int loc = getdp(x + 1, vf | (1<<i)) + cost[x][i];
		ret = min(ret, loc);
	}
	return ret;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> cost[i][j];
		
	// fill dp with -1
	memset(dp, 0xFF, sizeof(dp));
	
	cout << getdp(0, 0);
}
