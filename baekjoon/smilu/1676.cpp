#include <cstdio>

int N;
int cnt[2];

int main(void)
{
	scanf("%d", &N);
	for(int i = 2; i <= N; ++i) {
		int val = i;
		while((val % 2) == 0) {
			++cnt[0];
			val /= 2;
		}
		while((val % 5) == 0) {
			++cnt[1];
			val /= 5;
		}
	}
	printf("%d", cnt[0] < cnt[1] ? cnt[0] : cnt[1]);
}