
#include <iostream>

using namespace std;

#define MOD 1000000000

int N;
int dp[101][10][10][10];

int get_dp(int length, int last, int left, int right)
{
	if(dp[length][last][left][right] != -1) {
		return dp[length][last][left][right];
	}
	int ret = 0;

	// length - 1
	// last - 1, last + 1
	// left
	// right`````````````````
}

int main(void)
{
	scanf("%d", &N);

	for(int i=0; i<101; ++i)
		for(int j=0; j<10; ++j)
			for(int k=0; k<10; ++k)
				for(int l=0; l<10; ++l)
					dp[i][j][k][l] = -1;

	for(int i=1; i<=9; ++i) {
		dp[1][i][i][i] = 1;
	}

	int ans = 0;
	for(int i=0; i<10; ++i) {
		ans = (ans + get_dp(N, i, 0, 9)) % MOD;
	}
	printf("%d", ans)

	return 0;
}
