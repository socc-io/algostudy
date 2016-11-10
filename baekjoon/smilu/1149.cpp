#include <stdio.h>

int min2(int a, int b)
{
	return a < b ? a : b;
}

int min3(int a, int b, int c)
{
	return min2(min2(a, b), c);
}

int main(int argc, char** argv)
{
	int N;
	scanf("%d", &N);
	int cost[1000][3];
	int min_cost[1000][3];
	int i,j;
	for(i=0;i<N;++i) {
		scanf("%d %d %d", &cost[i][0], &cost[i][1], &cost[i][2]);
	}
	min_cost[0][0] = cost[0][0];
	min_cost[0][1] = cost[0][1];
	min_cost[0][2] = cost[0][2];
	for(i=1;i<N;++i) {
		min_cost[i][0] = min2(min_cost[i-1][1] + cost[i][0], min_cost[i-1][2] + cost[i][0]);
		min_cost[i][1] = min2(min_cost[i-1][0] + cost[i][1], min_cost[i-1][2] + cost[i][1]);
		min_cost[i][2] = min2(min_cost[i-1][0] + cost[i][2], min_cost[i-1][1] + cost[i][2]);
	}
	int res = min3(min_cost[N-1][0], min_cost[N-1][1], min_cost[N-1][2]);
	printf("%d", res);
	return 0;
}