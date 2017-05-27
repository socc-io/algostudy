#include <cstdio>
#include <cstdlib>
#include <cstring>

char a[101];
char b[101];
char c[101];
int lcs[101][101][101];

int a_len, b_len, c_len;

int max2(int a, int b) { return a>b ? a:b; }
int max3(int a, int b, int c) { return max2(max2(a, b), c); }

int LCS()
{
	for(int i=0; i<a_len; ++i) for(int j=0; j<b_len; ++j)
		lcs[i][j][0] = 0;
	for(int i=0; i<b_len; ++i) for(int j=0; j<c_len; ++j)
		lcs[0][i][j] = 0;
	for(int i=0; i<a_len; ++i) for(int j=0; j<c_len; ++j)
		lcs[i][0][j] = 0;

	for(int i=1; i<=a_len; ++i) {
		for(int j=1; j<=b_len; ++j) {
			for(int k=1; k<=c_len; ++k) {
				if(a[i-1] == b[j-1] && b[j-1] == c[k-1]) {
					lcs[i][j][k] = lcs[i-1][j-1][k-1] + 1;
				}
				else {
					lcs[i][j][k] = max3(lcs[i-1][j][k], lcs[i][j-1][k], lcs[i][j][k-1]);
				}
			}
		}
	}
	return lcs[a_len][b_len][c_len];
}

int main(void)
{
	scanf("%s%s%s", a, b, c);
	a_len = strlen(a);
	b_len = strlen(b);
	c_len = strlen(c);
	printf("%d", LCS());
}