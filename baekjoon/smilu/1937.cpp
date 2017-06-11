#include <cstdio>
#include <cstdlib>

int n;
int tile[501][501];
int dp[501][501];

int max(int a, int b) { return a>b ? a:b; }
int max4(int a, int b, int c, int d) { return max(a, max(b, max(c, d))); }

int findCapacity(int x, int y, int k)
{
	int t = tile[x][y];
	if(k >= t || x < 0 || y < 0 || x >= n || y >= n) return 0;
	if(dp[x][y] != -1) return dp[x][y];
	dp[x][y] = max4(
			findCapacity(x+1, y, t),
			findCapacity(x-1, y, t),
			findCapacity(x, y+1, t),
			findCapacity(x, y-1, t)
		) + 1;
	return dp[x][y];
}

int main(void)
{
	scanf("%d", &n);
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) {
			scanf("%d", &(tile[i][j]));
			dp[i][j] = -1;
		}
	}
	int maxCapacity = -1;
	for(int i=0; i<n; ++i) for(int j=0; j<n; ++j) {
		maxCapacity = max(maxCapacity, findCapacity(i, j, -1));
	}
	printf("%d\n", maxCapacity);
}	