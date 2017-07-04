#include <cstdio>

int main(void)
{
	int N, F;
	scanf("%d%d", &N, &F);

	int res = ((((N / 100) * 100) + F - 1) / F) * F % 100;
	if (res < 10) printf("0");
	printf("%d", res);
}