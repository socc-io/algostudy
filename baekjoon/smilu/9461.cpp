#include <cstdio>

long long dp[101] = {0, 1, 1, 1, 2, 2, 3, 4, 5, 7, 9};

int main(void)
{
	for(int i = 11; i < 101; ++i) {
		dp[i] = dp[i - 1] + dp[i - 5];
	}

	int T, N;
	scanf("%d", &T);
	for(int t = 0; t < T; ++t) {
		scanf("%d", &N);
		printf("%lld\n", dp[N]);
	}
}