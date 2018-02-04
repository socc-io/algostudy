
#include <iostream>
#include <cstring>

using namespace std;

#define MOD 1000000

char s[5001];
int dp[5000], len;

int main(void)
{
	scanf("%s", s);
	len = strlen(s);
	if(s[0] == '0') {
		printf("0");
		return 0;
	}
	dp[0] = 1;
	dp[1] = 1;
	for(int i=2; i<=len; ++i) {
		if(s[i-1] != '0') {
			dp[i] = dp[i-1];
		}
		if((s[i-2]-'0')*10+(s[i-1]-'0') <= 26 && s[i-2] != '0') {
			dp[i] = (dp[i] + dp[i-2]) % MOD;
		}
	}
	printf("%d", dp[len]);
}