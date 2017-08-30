#include <cstdio>

#define MAX_PRIME (123456 * 2 + 1)

bool prime[MAX_PRIME];

int main(void)
{
	for(int i = 2; i < MAX_PRIME; ++i) {
		if(prime[i]) continue;
		for(int j = i << 1; j < MAX_PRIME; j += i) {
			prime[j] = true;
		}
	}
	while(true) {
		int cnt = 0, N;
		scanf("%d", &N);
		if(N == 0) break;
		for(int i = N+1; i <= (N << 1); ++i) {
			if(!prime[i]) ++cnt;
		}
		printf("%d\n", cnt);
	}
}