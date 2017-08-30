#include <cstdio>

int dp[100][100][100];

int get(int a, int b, int c)
{
	if(dp[a][b][c]) return dp[a][b][c];
	int ans = 0, tmp;
	for(int i = a+1; i < b; ++i) {
		tmp = get(a, i, b) + 1;
		if(tmp > ans) ans = tmp;
	}
	for(int i = b+1; i < c; ++i) {
		tmp = get(b, i, c) + 1;
		if(tmp > ans) ans = tmp;
	}
	dp[a][b][c] = ans;
	return ans;
}

int main(void)
{
	int A, B, C;
	scanf("%d%d%d", &A, &B, &C);
	printf("%d", get(A, B, C));
}