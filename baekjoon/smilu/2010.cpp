#include <cstdio>

int main(void)
{
	int N, sum = 1, tmp;
	scanf("%d", &N);
	for(int i=0; i<N; ++i) {
		scanf("%d", &tmp);
		sum += --tmp;
	}
	printf("%d", sum);
}