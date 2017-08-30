#include <cstdio>

#define gc() getchar_unlocked()
#define pc(x) putchar_unlocked(x)

int N, M, K, a, b, c, d, r, si;
int dp[301][301];
char s[20];

int getint()
{
	char ch; int res = 0; bool m = false;
	while(('0' > (ch = gc()) || ch > '9') && ch != '-') {}
	if(ch == '-') m = true;
	else res = ch - '0';
	while('0' <= (ch = gc()) && ch <= '9') {
		res = res * 10 + ch - '0';
	}
	return res * (m ? -1 : 1);
}

int main(void)
{
	N = getint(); M = getint();
	for(int i = 1; i <= N; ++i) for(int j = 1; j <= M; ++j) {
		dp[i][j] = getint() + dp[i-1][j] + dp[i][j-1] - dp[i-1][j-1];
	}
	for(K = getint();K--;) {
		a = getint()-1; b = getint()-1; c = getint(); d = getint();
		printf("%d\n", dp[c][d] - dp[a][d] - dp[c][b] + dp[a][b]);
	}
}