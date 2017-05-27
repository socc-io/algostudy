#include <cstdio>
#include <cstdlib>

int dp[1000001][32];

int main(void)
{
	int N;
	scanf("%d", &N);
	dp[1][0] = 1;
	for(int i=2; i<=N; ++i) {
		dp[i][0] = 1;
		for(int j=1; (1<<j)<=i; ++j) {
			if((1<<j) == i) {
				dp[i][j] = dp[i][j-1] + 1;
				break;
			}
			int k=j;
			while((1<<k) > i-(1<<j)) --k;
			dp[i][j] = ( dp[i][j-1] + dp[i-(1<<j)][k] );
			dp[i][j] %= 1000000000;
		}
	}

	// for(int i=1; i<=N; ++i) {
	// 	for(int j=0; (1<<j)<=i; ++j) {
	// 		printf("%d ", dp[i][j]);
	// 	} printf("\n");
	// }

	int p=0;
	while((1<<p) <= N) ++p;
	printf("%d\n", dp[N][p-1]);
}
