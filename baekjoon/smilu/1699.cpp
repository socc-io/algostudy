#include <cstdio>

int dp[100001];

int main(void)
{
	int N;
	scanf("%d", &N);
	dp[0] = 0;
	for(int i = 1; i <= N; ++i) {
		int ml = 100000;
		for(int j=1;;++j) {
			int w = i - j*j;
			if(w < 0) break;
			if(dp[w] < ml) ml = dp[w];
		}
		dp[i] = ml + 1;
	}
	printf("%d", dp[N]);
}