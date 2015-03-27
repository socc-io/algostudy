#pragma warning(disable: 4996)
#include <stdio.h>

void hanoi(int origin, int middle, int dest, int n){
	if (n == 1){
		printf("%d -> %d\n", origin, dest);
		return;
	}
	hanoi(origin, dest, middle, n - 1);
	printf("%d -> %d\n", origin, dest);
	hanoi(middle, origin, dest, n - 1);
}

int main(void){
	int num;

	scanf("%d", &num);

	hanoi(1, 2, 3, num);
	return 0;
}
