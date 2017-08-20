#include <cstdio>

int main(void)
{
	int T, M, N, x, y, tmp, cur, i;
	long long time;
	scanf("%d", &T);
	for(int t = 0; t < T; ++t) {
		scanf("%d%d%d%d", &M, &N, &x, &y);
		if(M > N) {
			tmp = M;
			M = N;
			N = tmp;
			tmp = x;
			x = y;
			y = tmp;
		}
		--x; --y;
		time = x;
		for(cur = x, i = 0; cur != y && i < N; cur = (cur + M) % N, time += M, ++i);
		if(i == N) printf("-1\n");
		else printf("%lld\n", time + 1);
	}
}