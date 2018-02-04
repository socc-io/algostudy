#include <iostream>

double p[3];
double dp[21][41];

int main(void)
{
	scanf("%lf%lf%lf", p, p+1, p+2);
	dp[0][20] = 1;
	for(int stage = 1; stage <= 20; ++stage) {
		for(int point = 0; point <= 41; ++point) {
			dp[stage][point] = 
				(point > 0 ? dp[stage-1][point-1] * p[0] : 0) + 
				(point < 40 ? dp[stage-1][point+1] * p[1] : 0) +
				(dp[stage-1][point] * p[2]);
		}
	}
	double res;
	for(int i=0; i<4; ++i) {
		res = 0;
		for(int j=i*10; j<(i+1)*10; ++j) {
			res += dp[20][j];
		}
		printf("%.8lf\n", res);
	}
	printf("%.8lf\n", dp[20][40]);
}
