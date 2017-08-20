#include <cstdio>

int main(void)
{
	int N;
	scanf("%d", &N);

	if(N == 1) {
		printf("0\n");
		return 0;
	}

	long long ans = 2;

	for(int i = 2; i < N; ++i) {
		ans = (ans * 3) % 1000000009;
	}

	printf("%lld\n", ans);

	return 0;
}