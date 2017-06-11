#include <cstdio>
#include <cstdlib>
#include <cstring>


char a[1000];
char b[1000];
int lcs[1001][1001];

int a_len, b_len;

template <class T>
T max(T a, T b) { return a>b ? a:b; }

int LCS()
{
	for(int i=0; i<a_len; ++i) {
		lcs[i][0] = 0;
	}
	for(int i=0; i<b_len; ++i) {
		lcs[0][i] = 0;
	}
	for(int i=1; i<=a_len; ++i) {
		for(int j=1; j<=b_len; ++j) {
			if(a[i-1] == b[j-1]) {
				lcs[i][j] = lcs[i-1][j-1] + 1;
			}
			else {
				lcs[i][j] = max(lcs[i-1][j], lcs[i][j-1]);
			}
		}
	}
	return lcs[a_len][b_len];
}

int main(void)
{
	scanf("%s%s", a, b);
	a_len = strlen(a);
	b_len = strlen(b);
	printf("%d", LCS());
}