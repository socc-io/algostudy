#include <cstdio>
#include <cmath>

int main(void)
{
	int X, I, S;
	scanf("%d", &X);
	I = (1+sqrt(8*X - 7)) / 2;
	S = I * (I - 1) / 2 + 1;
	if(I & 1) printf("%d/%d", I-X+S, 1+X-S);
	else      printf("%d/%d", 1+X-S, I-X+S);
}