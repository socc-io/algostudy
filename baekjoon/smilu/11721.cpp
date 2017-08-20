#include <cstdio>

char buf[101];

int main(void)
{
	scanf("%s", buf);
	char *ch; int i;
	for(ch = buf, i = 0; (*ch) != '\0'; ++ch, ++i) {
		if(i >= 10) {
			putchar('\n');
			i = 0;
		}
		putchar(*ch);
	}
}