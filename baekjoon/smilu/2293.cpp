#include <cstdio>

int N, K;
int cost[100];

int dp[2][10001];

int main(void)
{
	scanf("%d%d", &N, &K);
	for(int i = 0; i < N; ++i) scanf("%d", cost + i);
	dp[0][0] = 1;
	
	for(int i = 0; i < N; ++i) {
		for(int j = 0; j <= K; ++j) {
			for(int k = j; k >= 0; k -= cost[i]) {
				dp[1][j] += dp[0][k];
			}
		}
		for(int j = 0; j <= K; ++j) {
			dp[0][j] = dp[1][j];
			dp[1][j] = 0;
		}
	}

	printf("%d", dp[0][K]);
}