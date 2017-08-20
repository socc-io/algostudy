#include <cstdio>

int mat[15][15];

int main(void)
{
	int T, k, n;
	scanf("%d", &T);
	for(int i = 0; i < 15; ++i) {
		mat[i][0] = 1;
		mat[0][i] = i+1;
	}
	for(int i = 1; i < 15; ++i) {
		for(int j = 1; j < 15; ++j) {
			mat[i][j] = mat[i-1][j] + mat[i][j-1];
		}
	}
	for(int t = 0; t < T; ++t) {
		scanf("%d%d", &k, &n);
		printf("%d\n", mat[k][n-1]);
	}
}