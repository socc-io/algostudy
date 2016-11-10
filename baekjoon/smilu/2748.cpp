#include <stdio.h>

int main(void)
{
	int n;
	long long arr[200];
	scanf("%d", &n);
	arr[0] = 0;
	arr[1] = 1;
	for(int i=2; i<=n; ++i) {
		arr[i] = arr[i-2] + arr[i-1];
	}
	printf("%lld", arr[n]);

	return 0;
}