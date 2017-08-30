#include <cstdio>

int main(void)
{
	int N;
	scanf("%d", &N);
	int ans = 1;
	for(int i = 1; i <= N; ++i) ans *= i;
	printf("%d", ans);
}