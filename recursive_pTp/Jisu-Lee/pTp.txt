#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>

void print(int n){

	if (n == 1){
		printf("1");
		return;
	}

	print(n - 1);
	printf("%d", n);
	print(n - 1);
}

int main(void){
	int num;

	scanf("%d", &num);

	print(num);
	//puts("");
	return 0;

}


