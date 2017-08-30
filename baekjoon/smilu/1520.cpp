#include <cstdio>

int height[500][500];
int dp[500][500];
int M, N;

const int dir[4][2] = {1, 0, -1, 0, 0, 1, 0, -1};

int get(int a, int b)
{
	if(dp[a][b] != -1) return dp[a][b];
	dp[a][b] = 0;
	for(int d=0; d<4; ++d) {
		int na = a + dir[d][0], nb = b + dir[d][1];
		if(na < 0 || na >= M || nb < 0 || nb >= N) continue;
		if(height[na][nb] <= height[a][b]) continue;
		dp[a][b] += get(na, nb);
	}
	return dp[a][b];
}

int main(void)
{
	scanf("%d%d", &M, &N);
	for(int i = 0; i < M; ++i) {
		for(int j = 0; j < N; ++j) {
			scanf("%d", height[i] + j);
			dp[i][j] = -1;
		}
	}
	dp[0][0] = 1;
	printf("%d", get(M-1, N-1));
}