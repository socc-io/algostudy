#include <cstdio>

int T, N;
char buf[200];

int main(void)
{
	scanf("%d", &T);
	for(int t = 0; t < T; ++t) {
		scanf("%d%s", &N, buf);
		for(char *ch = buf; (*ch) != '\0'; ++ch) {
			for(int i = 0; i < N; ++i) {
				putchar(*ch);
			}
		}
		putchar('\n');
	}
}