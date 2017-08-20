#include <cstdio>
int main()
{
	int r1, c1, r2, c2, x, y, i, j, max_val = 1, max_len = 0, mat[50][5];
	scanf("%d%d%d%d", &r1, &c1, &r2, &c2);
	for(x=r1, i=0; x<=r2; ++x, ++i) {
		for(y=c1, j=0; y<=c2; ++y, ++j) {
			mat[i][j] = 1 + (y <= x ? (y >= -x ? 4*x*x + 3*x + y : 4*y*y - y + x) : (y >= -x ? 4*y*y - 3*y - x : 4*x*x + x - y));
			if(max_val<mat[i][j]) max_val=mat[i][j];
		}
	}
	for(;max_val;max_val/=10) ++max_len;
	for(i=0; i<=r2-r1; ++i) {
		for(j=0; j<=c2-c1; ++j) {
			printf("%*d ",max_len,mat[i][j]);
		} puts("");
	}
}