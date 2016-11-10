#include <stdio.h>

int max2(int a, int b)
{
	return a > b ? a : b;
}

int main(void)
{
	int stair[400];
	int n;
	int max_score[400][2];
	scanf("%d", &n);
	for(int i=0;i<n;++i){
		scanf("%d", &stair[i]);
	}
	if(n == 1) {
		printf("%d", stair[0]);
		return 0;
	}
	else if(n == 2) {
		printf("%d", stair[0] + stair[1]);
		return 0;
	}
	max_score[0][0] = stair[0];
	max_score[0][1] = -1;
	max_score[1][0] = stair[1];
	max_score[1][1] = stair[0] + stair[1];
	for(int i=2;i<n;++i){
		max_score[i][0] = max2(max_score[i-2][0], max_score[i-2][1]) + stair[i];
		max_score[i][1] = max_score[i-1][0] + stair[i];
	}
	int best = max2(max_score[n-1][0], max_score[n-1][1]);
	printf("%d", best);

	return 0;
}