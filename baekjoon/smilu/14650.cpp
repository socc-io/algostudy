#include <cstdio>

int main(void)
{
	int N;
	scanf("%d", &N);

	if(N == 1) {
		printf("0\n");
		return 0;
	}

	int ans = 2;

	for(int i = 2; i < N; ++i) {
		ans *= 3;
	}

	printf("%d\n", ans);

	return 0;
}