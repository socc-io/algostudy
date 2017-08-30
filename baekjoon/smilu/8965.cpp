#include <cstdio>
#include <cstring>

char F[101];
int len;
int compare(int a, int b)
{
	for(int i = 0; i < len; ++i) {
		if(F[a] < F[b]) return 1;
		else if(F[a] > F[b]) return -1;
		a = (a + 1) % len;
		b = (b + 1) % len;
	}
	return 0;
}

int main(void)
{
	int T;
	for(scanf("%d", &T); T--;) {
		scanf("%s", F);
		len = strlen(F);
		int m = 0;
		for(int i = 1; i < len; ++i) {
			if(compare(m, i) < 0) m = i;
		}
		for(int i = 0; i < len; ++i) {
			putchar(F[m]);
			m = (m + 1) % len;
		} putchar('\n');
	}
}