#include <stdio.h>

int main(void)
{
	int base;
	scanf("%d", &base);
	int k;
	scanf("%d", &k);
	while(k != 0) {
		if(k % base == 0) {
			printf("%d is a multiple of %d.\n", k, base);
		}
		else {
			printf("%d is NOT a multiple of %d.\n", k, base);
		}
		scanf("%d", &k);
	}
	return 0;
}