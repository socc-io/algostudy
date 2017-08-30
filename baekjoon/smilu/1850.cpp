#include <cstdio>

typedef unsigned long long llu;

llu gcd(llu a, llu b)
{
	llu tmp;
	if(a == 0) return b;
	if(a < b) {
		b = b % a;
	}
	while(b) {
		tmp = a % b;
		a = b;
		b = tmp;
	}
	return a;
}


int main(void)
{
	llu a, b;
	scanf("%llu%llu", &a, &b);
	llu g = gcd(a, b);
	for(int i = 0; i < g; ++i) {
		putchar('1');
	}
}