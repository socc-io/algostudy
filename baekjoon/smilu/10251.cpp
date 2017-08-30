#include <iostream>

#define INF (0x7FFFFFFF-(200000))

using namespace std;

int T, M, N, L, G, tmp, cur, maxk;

int cost[100][100][2];
int dp[100][100][201][2];

int getint()
{
	int res = getchar() - '0';
	char ch;
	while('0' <= (ch = getchar()) && ch <= '9') {
		res = res * 10 + ch - '0';
	}
	return res;
}

int main(void)
{
	T = getint();
	while(T--) {
		M = getint(), N = getint(), L = getint(), G = getint();
		maxk = M+N-2;
		for(int i = 0; i < M; ++i) for(int j = 0; j < N - 1; ++j) {
			cost[i][j][1] = getint();
		}
		for(int i = 0; i < M - 1; ++i) for(int j = 0; j < N; ++j) {
			cost[i][j][0] = getint(); 
		}
		for(int i = 0; i < M; ++i) for(int j = 0; j < N; ++j)
			for(int k = 0; k < maxk; ++k) {
				dp[i][j][k][0] = INF;
				dp[i][j][k][1] = INF;
		}
		dp[0][0][0][0] = 0;
		dp[0][0][0][1] = 0;
		tmp = 0;
		for(int i = 1; i < M; ++i) {
			tmp += cost[i-1][0][0];
			dp[i][0][0][0] = tmp;
		}
		tmp = 0;
		for(int i = 1; i < N; ++i) {
			tmp += cost[0][i-1][1];
			dp[0][i][0][1] = tmp;
		}
		for(int x = 1; x < M; ++x) for(int y = 1; y < N; ++y) {
			for(int t = 1; t < x+y; ++t) {
				dp[x][y][t][0] = min(dp[x-1][y][t][0], dp[x-1][y][t-1][1]) + cost[x-1][y][0];
				dp[x][y][t][1] = min(dp[x][y-1][t-1][0], dp[x][y-1][t][1]) + cost[x][y-1][1];
			}
		}
		int ans = 1;
		for(; ans < maxk; ++ans) {
			if(dp[M-1][N-1][ans][0] <= G || dp[M-1][N-1][ans][1] <= G) {
				printf("%d\n", ans + L*(maxk));
				break;
			}
		}
		if(ans == maxk) puts("-1");
	}
}