#include <cstdio>

#define MOD 1000007

int map[201][201];

int main(void)
{
	int w, h, x, y;
	scanf("%d%d%d%d", &w,&h,&x,&y);
	for(int i=0;i<w;++i) map[i][0] = 1;
	for(int i=1;i<h;++i) map[0][i] = 1;
	for(int i=1;i<w;++i) for(int j=1;j<h;++j) {
		map[i][j] = (map[i-1][j] + map[i][j-1]) % MOD;
	}
	printf("%d", ((unsigned long long)map[x-1][y-1] * map[w-x][h-y])%MOD);
}