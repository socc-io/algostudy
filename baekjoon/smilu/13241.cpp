#include <cstdio>

typedef long long lld;

lld gcd(lld a, lld b)
{
	lld tmp;
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
lld lcm(lld a, lld b)
{
	return a * b / gcd(a, b);
}
int main(void)
{
	lld a, b;
	scanf("%lld%lld", &a, &b);
	printf("%lld", lcm(a, b));
}