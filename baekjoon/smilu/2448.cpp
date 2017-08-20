#include <cstdio>

void print(int level, int line)
{
	if(level == 3) {
		     if(line == 0) printf("  *  ");
		else if(line == 1) printf(" * * ");
		else if(line == 2) printf("*****");
		return;
	}
	int prev_level = level >> 1;
	if(line < prev_level) {
		for(int i = 0; i < prev_level; ++i) {
			putchar(' ');
		}
		print(prev_level, line);
		for(int i = 0; i < prev_level; ++i) {
			putchar(' ');
		}
	} else {
		print(prev_level, line - prev_level);
		putchar(' ');
		print(prev_level, line - prev_level);
	}
}

int main(void)
{
	int N;
	scanf("%d", &N);
	for(int i=0; i<N; ++i) {
		print(N, i);
		putchar('\n');
	}
}
