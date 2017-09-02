#include <iostream>
#include <vector>
using namespace std; 

#define K_MAX 1000000000
#define PRIME_MAX 40559

bool prime[PRIME_MAX+1];
bool dp[K_MAX+1];

int main(void)
{
    int K;
    scanf("%d", &K);

    // calc primes
    puts("calc primes started");
    prime[0] = true, prime[1] = true;
    int prime_cnt = 0;
    for(int i=2; i<=PRIME_MAX; ++i) {
        if(prime[i]) continue;
        ++prime_cnt;
        for(int j=i<<1; j<=PRIME_MAX;  j+=i) {
            prime[j] = true;
        }
        int m = i*i;
        for(int j=m; j<=K_MAX; j+=m) {
            dp[j] = true;
        }
    }
    printf("calc primes complete: %d\n", prime_cnt);
    int cnt = 0;
    for(int i=1; i<=K_MAX; ++i) {
        if(dp[i] == false) ++cnt;
        if(cnt >= K) {
            printf("%d\n", i);
            break;
        }
    }
    puts("complete");
}
