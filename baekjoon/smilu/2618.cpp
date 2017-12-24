#include<iostream>
using namespace std;

#define INF 1234567890

int n, w;
int x[1002], y[1002], fx[1002][1002], fy[1002][1002], dp[1002][1002];

inline int dist(int a, int b) {
	return abs(x[a] - x[b]) + abs(y[a] - y[b]);
}

inline void update(int xx, int yy, int fxx, int fyy, int w) {
	if(w < dp[xx][yy]) {
		dp[xx][yy] = w;
		fx[xx][yy] = fxx;
		fy[xx][yy] = fyy;
	}
}

void trace(int xx, int yy)
{
	if(xx == 0 && yy == 1) return;
	int fxx = fx[xx][yy], fyy = fy[xx][yy];
	trace(fxx, fyy);
	if(fxx != xx) {
		puts("1");
	} else {
		puts("2");
	}
}

int main()
{
	scanf("%d%d", &n, &w);
	w += 2;
	x[0] = 1, y[0] = 1;
	x[1] = n, y[1] = n;
	for(int i=2; i<w; ++i) scanf("%d%d", x+i, y+i);
	for(int i=0; i<w; ++i) for(int j=0; j<w; ++j) dp[i][j] = INF;
	dp[0][1] = 0;
	for(int i=0; i<w; ++i) {
		for(int j=0; j<w; ++j) {
			if(i < j) {
				if(i + 1 == j) {
					for(int k=0; k<i; ++k) {
						update(i, j, i, k, dp[i][k] + dist(k, j));
					}
				} else {
					update(i, j, i, j-1, dp[i][j-1] + dist(j-1, j));
				}
			} else if(i > j) {
				if(j + 1 == i) {
					for(int k=0; k<j; ++k) {
						update(i, j, k, j, dp[k][j] + dist(k, i));
					}
				} else {
					update(i, j, i-1, j, dp[i-1][j] + dist(i-1, i));
				}
			}
		}
	}
	int answ = INF, ansx, ansy;
	for(int i=0; i<w; ++i) {
		if(dp[i][w-1] < answ) {
			answ = dp[i][w-1];
			ansx = i, ansy = w-1;
		}
		if(dp[w-1][i] < answ) {
			answ = dp[w-1][i];
			ansx = w-1, ansy = i;
		}
	}
	printf("%d\n", answ);
	trace(ansx, ansy);
}