#include <cstdio>
#include <cstdlib>

int w, h;
int tile[1001][1001];
int dp[1001][1001];

int max(int a, int b) { return a > b ? a : b; }

int visit(int x, int y)
{
	if(x == 1 && y == 1) return tile[1][1];
	if(x == 1) return dp[x][y-1] + tile[x][y];
	if(y == 1) return dp[x-1][y] + tile[x][y];
	return max(max(dp[x-1][y], dp[x][y-1]), dp[x-1][y-1]) + tile[x][y];
}

int main(void)
{
	scanf("%d%d", &h, &w);
	for(int i=1; i<=h; ++i) {
		for(int j=1; j<=w; ++j) {
			scanf("%d", &(tile[i][j]));
		}
	}
	for(int i=1; i<=h; ++i) {
		for(int j=1; j<=w; ++j) {
			dp[i][j] = visit(i, j);
		}
	}
	printf("%d\n", dp[h][w]);

	return 0;
}