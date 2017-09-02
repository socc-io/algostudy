#include <cstdio>

int N;
int A[1000];
int dp[1000];

int main(void)
{
    scanf("%d", &N);
    for(int i=0; i<N; ++i) {
        scanf("%d", A + i);
    }
    for(int i=0; i<N; ++i) {
        dp[i] = 1;
        for(int j=0; j<i; ++j) {
            if(A[j] < A[i] && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
            }
        }
    }
    int ans = 0;
    for(int i=0; i<N; ++i) {
        if(ans < dp[i]) {
            ans = dp[i];
        }
    }
    printf("%d", ans);
} 
