#include <cstdio>

const char *name = "DCBAE";

int main(void)
{
	for(int i = 0; i < 3; ++i) {
		int cnt = 0;
		for(int j = 0; j < 4; ++j) {
			cnt += getchar() - '0';
			getchar();
		}
		putchar(name[cnt]);
		putchar('\n');
	}
}