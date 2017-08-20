#include <cstdio>

int main(void)
{
	int A, B, C;
	scanf("%d%d%d", &A, &B, &C); 
	printf("%d\n%d\n%d\n%d", (A+B)%C, (A+B)%C, (A*B)%C, (A*B)%C);
}