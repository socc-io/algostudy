#include <stdio.h>

int main(void)
{
	int N, K;
	scanf("%d %d", &N, &K);
	if(K > (N / 2)) {
		K = N - K;
	}
	int res = 1;
	for(int i=N-K+1; i<=N; ++i) {
		res *= i;
	}
	for(int i=2; i<=K; ++i) {
		res /= i;
	}
	printf("%d\n", res);

	return 0;
}