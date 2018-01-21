
/*
 * Author: smilu97
 */

#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

#define INF 1234567890

int N;
double x[512];
double y[512];
double dp[512][512];
double mem_dist[512][512];

double dist(int i, int j)
{
	if(mem_dist[i][j] == -1) {
		double dx = x[i] - x[j];
		double dy = y[i] - y[j];
		mem_dist[i][j] = sqrt(dx*dx + dy*dy);
	}
	return mem_dist[i][j];
}

void do_task()
{
	scanf("%d", &N);
	for(int i=0; i<N; ++i) {
		scanf("%lf%lf", x+i, y+i);
	}

	for(int i=0; i<N; ++i) for(int j=0; j<N; ++j) {
		mem_dist[i][j] = -1;
		dp[i][j] = INF;
	}

	dp[1][0] = dist(1, 0);
	dp[0][1] = dp[1][0];
	for(int i=2; i<N; ++i) {
		for(int j=0; j<i; ++j) {
			if(j+1 == i) {
				for(int k=0; k<j; ++k) {
					dp[i][j] = min(dp[i][j], dp[k][j] + dist(i, k));
				}
			} else {
				dp[i][j] = dp[i-1][j] + dist(i, i-1);
			}
			dp[j][i] = dp[i][j];
		}
	}

	dp[N-1][N-1] = INF;
	for(int i=0; i<N; ++i) {
		dp[N-1][N-1] = min(dp[N-1][N-1], dp[N-1][i] + dist(N-1, i));
	}

	printf("%.12f\n", dp[N-1][N-1]);
}

int main(void)
{
	int T;
	scanf("%d", &T);
	while(T--) {
		do_task();
	}
	return 0;
}