#include <cstdio>

typedef unsigned long long ull;

ull min, max;

bool dp[1000001];
bool prime[1000001]; // prime[n] = 1 => n은 소수가 아님

int main(void)
{
    scanf("%llu%llu", &min, &max);
    prime[0] = 1;
    prime[1] = 1;
    int cnt = max - min + 1;
    for(ull i=2; i*i<=max; ++i) {
        if(prime[i]) continue;
        for(int j=i*2; j<1000001; j+=i) {
            prime[j] = true;
        }
        ull k = i*i;
        for(ull j=((min+k-1) / k) * k; j<=max; j+=k) {
            if(dp[j-min] == false) {
                dp[j-min] = true;
                --cnt;
            }
        }
    }
    printf("%d", cnt);
}


