#include <cstdio>

bool prime[10001];
int partition[10001][2];

int primes[10001];
int prime_num;

int main(void)
{
	for(int i = 2; i < 10001; ++i) {
		if(prime[i]) continue;
		primes[prime_num++] = i;
		for(int j = (i << 1); j < 10001; j += i) {
			prime[j] = true;
		}
	}

	int T,N;
	scanf("%d", &T);
	for(int t = 0; t < T; ++t) {
		scanf("%d", &N);
		bool found = false;
		for(int d = 0;; ++d) {
			for(int i = 0; i < prime_num - d; ++i) {
				if(primes[i] + primes[i+d] == N) {
					printf("%d %d\n", primes[i], primes[i+d]);
					found = true;
					break;
				}
			}
			if(found) break;
		}
	}
}