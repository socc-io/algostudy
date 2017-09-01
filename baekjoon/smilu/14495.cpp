#include <cstdio>

unsigned long long dp[117];

int main(void)
{
    int n;
    scanf("%d", &n);
    dp[1] = 1;
    dp[2] = 1;
    dp[3] = 1;
    for(int i=4; i<=n; ++i) {
        dp[i] = dp[i-1] + dp[i-3];
    }
    printf("%llu", dp[n]);
}

        
