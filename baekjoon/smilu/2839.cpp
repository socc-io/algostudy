#include <cstdio>

int main(void)
{
	int N;
	scanf("%d", &N);

	int d = N / 5;
	int r = N % 5;
	int k = r % 3;

	d -= k;
	if(d < 0) {
		printf("-1");
		return 0;
	}

	int cost = d + ((N - d*5) / 3);
	printf("%d", cost);

	return 0;
}