
#include <stdio.h>

#define MAX 32767

int main(void)
{
	int a, b;

	int up_a = 0, up_b;
	int down_a = 0, down_b;
	scanf("%d%d", &a, &b);

	for(int i=MAX; i > b; --i) {
		if (i % b == 0) continue;
		up_a = (a * i + (b / 2)) / b;
		up_b = i;
		break;
	}

	if (up_a != 0) {
		printf("%d %d", up_a, up_b);
		return 0;
	}

	for(int i=b-1; i >= 1; --i) {
		if (b % i == 0) continue;
		down_a = (a * i + (b / 2)) / b;
		down_b = i;
		break;
	}

	printf("%d %d", down_a, down_b);
}