#include <cstdio>

#define MOD 1000000000

int dp[101][10];

int main(void)
{
	int N;
	scanf("%d", &N);

	for(int i=1; i<10; ++i) {
		dp[1][i] = 1;
	}
	for(int i=2; i<=N; ++i) {
		for(int j=0; j<10; ++j) {
			if(j-1 >= 0) dp[i][j] = (dp[i][j] + dp[i-1][j-1]) % MOD;
			if(j+1 < 10) dp[i][j] = (dp[i][j] + dp[i-1][j+1]) % MOD;
		}
	}
	int ans = 0;
	for(int i=0; i<10; ++i) {
		ans += dp[N][i];
		ans %= MOD;
	}
	printf("%d", ans);
}