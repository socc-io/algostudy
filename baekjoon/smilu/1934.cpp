#include <cstdio>

int gcd(int a, int b)
{
	int tmp;
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
int lcm(int a, int b)
{
	return a * b / gcd(a, b);
}
int main(void)
{
	int T, a, b;
	scanf("%d", &T);
	for(int t = 0; t < T; ++t) {
		scanf("%d%d", &a, &b);
		printf("%d\n", lcm(a, b));
	}
}