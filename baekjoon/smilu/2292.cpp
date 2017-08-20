#include <cstdio>
#include <cmath>

int main(void)
{
	long long N;
	scanf("%lld", &N);
	printf("%lld", N == 1 ? 1 : (9 + (long long)sqrt(12 * N - 15)) / 6);
}