#include <cstdio>
#include <cstdlib>

int N;
int cards[1001];
int dp[1001][1001];

inline int max(int a, int b) {
	return a > b ? a : b;
}

int solve(int left, int right, int sum)
{
	if(left >= right) return 0;
	if(dp[left][right] != -1) return dp[left][right];
	int left_case  = sum - solve(left+1, right, sum-cards[left]);
	int right_case = sum - solve(left, right-1, sum-cards[right-1]);
	int result = max(left_case, right_case);
	dp[left][right] = result;
	return result;
}

void run()
{
	scanf("%d", &N);
	for(int i=0; i<N; ++i) {
		scanf("%d", cards+i);
	}
	for(int i=0; i<=N; ++i) {
		for(int j=0; j<=N; ++j) {
			dp[i][j] = -1;
		}
	}
	int sum=0;
	for(int i=0; i<N; ++i) sum += cards[i];
	printf("%d\n", solve(0, N, sum));
}

int main(void)
{
	int T;
	scanf("%d", &T);
	for(int i=0; i<T; ++i) {
		run();
	}
}