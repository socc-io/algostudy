#include <cstdio>
#include <cstdlib>
#include <cstring>

int main (void)
{
	int n;
	int a_sum = 0;
	int b_sum = 0;
	scanf("%d", &n);
	for(int i=0; i<n; ++i) {
		int a, b;
		scanf("%d%d", &a, &b);
		a_sum += a;
		b_sum += b;
	}
	printf("%d %d\n", a_sum, b_sum)
}