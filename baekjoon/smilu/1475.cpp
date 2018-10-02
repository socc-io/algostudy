#include <cstdio>

char s[10];
int cnt[10];

int main(void)
{
	scanf("%9s", s);

	for (char* ch = s; *ch != '\0'; ++ch) {
		++cnt[*ch - '0'];
	}
	
	int m = 0;
	for (int i = 0; i < 10; i++) {
		if (i == 6 || i == 9) continue;
		if (cnt[i] > m) {
			m = cnt[i];
		}
	}

	int n = (cnt[6] + cnt[9] + 1) / 2;
	if (n > m) m = n;

	printf("%d", m);

	return 0;
}
