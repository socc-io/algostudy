#include <cstdio>

inline bool is_number(char ch)
{
	return '0' <= ch && ch <= '9';
}

int getint()
{
	int res = 0;
	char ch;
	while(is_number(ch = getchar())) {
		res = res * 10 + ch - '0';
	}
	return res;
}

int main(void)
{
	printf("%.9f\n", (double)getint()/getint());

	return 0;
}