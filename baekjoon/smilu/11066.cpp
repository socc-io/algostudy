#include <cstdio>
#include <cstring>

#define INF 0x7FFFFFFF

int dp[501][501];

int T, K;
int amt[500];
int amtS[501];

int get(int a, int b)
{
	if(a == b) return 0;
	if(dp[a][b]) return dp[a][b];
	dp[a][b] = amtS[b+1] - amtS[a];
	int tmp = INF;
	for(int i = a; i < b; ++i) {
		int tmp2 = get(a, i) + get(i+1, b);
		if(tmp2 < tmp) tmp = tmp2;
	}
	dp[a][b] += tmp;
	return dp[a][b];
}

int main(void)
{
	scanf("%d", &T);
	for(int t = 0; t < T; ++t) {
		memset(dp, 0, sizeof(dp));
		scanf("%d", &K);
		for(int i = 0; i < K; ++i) scanf("%d", amt + i);
		amtS[0] = 0;
		for(int i = 1; i <= K; ++i) {
			amtS[i] = amtS[i-1] + amt[i-1];
		}
		printf("%d\n", get(0, K-1));
	}
}