#include <cstdio>
#include <cstdlib>

int N;
int QN;
int nums[2000];
int dp[2000][2000];

int get(int a, int b)
{
	if(a >= b) return 1;
	if(dp[a][b] != -1) return dp[a][b];
	if(nums[a] == nums[b] && get(a+1,b-1)) {
		dp[a][b] = 1;
		return 1;
	}
	dp[a][b] = 0;
	return 0;
}

int main(void)
{
	scanf("%d", &N);
	for(int i=0; i<N; ++i) {
		scanf("%d", nums+i);
	}
	for(int i=0; i<N; ++i) for(int j=0; j<N; ++j) dp[i][j] = -1;
	scanf("%d", &QN);
	for(int i=0; i<QN; ++i) {
		int a, b;
		scanf("%d%d", &a, &b);
		--a; --b;
		printf("%d\n", get(a,b));
	}
}