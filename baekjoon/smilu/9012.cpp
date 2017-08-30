#include <cstdio>

char buf[51];

int main(void)
{
	int T;
	scanf("%d", &T); getchar();
	for(int t = 0; t < T; ++t) {
		int level = 0;
		bool success = true;
		scanf("%s", buf);
		for(char *ch = buf; (*ch) != '\0'; ++ch) {
			if(*ch == '(') {
				++level;
			} else {
				--level;
				if(level < 0) {
					success = false;
					break;
				}
			}
		}
		if(level != 0) success = false;
		puts(success ? "YES" : "NO");
	}
}