#include <cstdio>

int main(void)
{
	int n, c = 0;
	scanf("%d", &n);

	n = 64 - n;
	while((n & 1) == 0 && c < 7) {
		n >>= 1;
		c++;
	}

	int cnt = 1;
	while(c < 6) {
		if((n & 1) == 0) cnt++;
		n >>= 1;
		++c;
	}

	printf("%d", cnt);
}