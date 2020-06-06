#include <bits/stdc++.h>
using namespace std;

int n, m, k;
int dp[300][301];
vector<pair<int,int>> edges[300];

int main(void)
{
	scanf("%d%d%d", &n, &m, &k);
	for(int i=0; i<k; ++i) {
		int from, to, benefit;
		scanf("%d%d%d", &from, &to, &benefit);
		if (from >= to) continue;
		--from; --to;
		edges[from].push_back(make_pair(to, benefit));
	}
	memset(dp, 0xff, sizeof(dp));
	dp[0][0] = 0;
	for(int i=0; i<n; ++i) {
		for(int j=0; j<m; ++j) {
			if (dp[i][j] == -1) continue;
			for (auto e: edges[i]) {
				dp[e.first][j+1] = max(dp[e.first][j+1], dp[i][j] + e.second);
				// printf("%d, %d: %d\n", e.first, j+1, dp[e.first][j+1]);
			}
		}
	}
	int ans = dp[n-1][0];
	for (int i = 1; i < m; i++) ans = max(ans, dp[n-1][i]);
	printf("%d", ans);
}