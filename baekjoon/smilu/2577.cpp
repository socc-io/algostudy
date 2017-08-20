#include <cstdio>

int cnt[10];

int main(void)
{
	int val = 1, tmp;
	for(int i = 0; i < 3; ++i) {
		scanf("%d", &tmp);
		val *= tmp;
	}
	while(val) {
		cnt[val % 10]++;
		val /= 10;
	}
	for(int i = 0; i < 10; ++i) {
		printf("%d\n", cnt[i]);
	}
}