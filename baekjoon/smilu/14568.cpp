#include <stdio.h>

int main(void)
{
	int n, a;
	scanf("%d", &n);
	if (n < 6) {
		printf("0\n");
		return 0;
	}
	a = n/2;
	printf("%d\n", (a*a - 3*a + 2)/2);
	return 0;
}