#include <cstdio>

int main(void)
{
	int a;
	scanf("%d", &a);
	for(int i = 1; i <= 9; ++i) {
		printf("%d * %d = %d\n", a, i, a*i);
	}
}