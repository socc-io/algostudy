
#include <cstdio>
#include <vector>

using namespace std;

int n, m, k;
int dp[300][301];
vector<pair<int,int>> edges[300];

int main(void)
{
	int best_dp = 0;

	scanf("%d%d%d", &n, &m, &k);
	for(int i=0; i<k; ++i) {
		int from, to, benefit;
		scanf("%d%d%d", &from, &to, &benefit);
		if (from >= to) continue;
		--from; --to;
		edges[from].push_back(make_pair(to, benefit));
	}
	for(int i=0; i<n; ++i) {
		for(int j=0; j<m; ++j) {
			for(auto eit = edges[i].begin(); eit != edges[i].end(); ++eit) {
				int new_dp = dp[i][j] + eit->second;
				if(new_dp > dp[eit->first][j+1]) {
					dp[eit->first][j+1] = new_dp;
				}
				if(new_dp < best_dp) {
					best_dp = new_dp;
				}
			}
		}
	}

	printf("%d", best_dp);

	return 0;
}