#include <cstdio>

int main(void)
{
	int T, H, W, N;
	scanf("%d", &T);
	for(int t = 0; t < T; ++t) {
		scanf("%d%d%d", &H, &W, &N); --N;
		printf("%d", N%H + 1);
		W = N/H + 1;
		if(W < 10) putchar('0');
		printf("%d\n", W);
	}
}