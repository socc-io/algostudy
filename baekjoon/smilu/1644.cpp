#include <iostream>
#include <vector>

using namespace std;

#define PRIME_MAX 4000001

int N;
bool prime[PRIME_MAX];
int dp[PRIME_MAX];
int dp2[PRIME_MAX];
int dp2_idx;
int dp2_start;

int main(void)
{
    for(int i=2; i<PRIME_MAX; ++i) {
        if(prime[i]) continue;
        for(int j = i<<1; j < PRIME_MAX; j += i) {
            prime[j] = true;
        }
        for(int j=dp2_start; j<dp2_idx; ++j) {
            dp2[j] += i;
        }
        dp2[dp2_idx++] = i;
        while(dp2[dp2_start] >= PRIME_MAX) ++dp2_start;
        for(int j=dp2_start; j<dp2_idx; ++j) {
            dp[dp2[j]]++;
        }
    }
    scanf("%d", &N);
    printf("%d", dp[N]);
}
    
