#include <cstdio>

int main(void)
{
	int a, b;
	while(1) {
		scanf("%d%d", &a, &b);
		if(a == 0 && b == 0) break;
		if(a-b < b) b = a-b;
		long long ans = 1;
		for(int i = 1; i <= b; ++i) {
			ans *= a - i + 1;
			ans /= i;
		}
		printf("%lld\n", ans);
	}
}