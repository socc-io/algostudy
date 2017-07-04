#include <cstdio>

int main(void)
{
	long long a, b, c;
	scanf("%lld%lld%lld", &a, &b, &c);
	printf("%lld", (6916*(--a) + 4845*(--b) + 4200*(--c)) % 7980 + 1);
}

// 15 28 19 7980
// 532 285 420
// 7 5 2
// 13 17 10
// 6916 4845 4200