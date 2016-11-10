#include <stdio.h>

int main(void)
{
	int a, b, c;
	scanf("%d %d %d", &a, &b, &c);
	if(a%b == 0){
		if(a/b == c) {
			printf("%d/%d=%d", a, b, c);
			return 0;
		}
	}
	if(a*b == c) {
		printf("%d*%d=%d", a, b, c);
		return 0;
	}
	if(a-b == c) {
		printf("%d-%d=%d", a, b, c);
		return 0;
	}
	if(a+b == c) {
		printf("%d+%d=%d", a, b, c);
		return 0;
	}
	if(b%c == 0){
		if(b/c == a) {
			printf("%d=%d/%d", a, b, c);
			return 0;
		}
	}
	if(b*c == a) {
		printf("%d=%d*%d", a, b, c);
		return 0;
	}
	if(b-c == a) {
		printf("%d=%d-%d", a, b, c);
		return 0;
	}
	if(b+c == a) {
		printf("%d=%d+%d", a, b, c);
		return 0;
	}
	return 0;
}