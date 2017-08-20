#include <cstdio>

inline bool is_numb(char ch)
{
	return ('0' <= ch && ch <= '9');
}

int getint()
{
	char ch;
	int res = 0;
	while( is_numb(ch = getchar()) ) {
		res = res * 10 + ch - '0';
	}
	return res;
}

int main(void)
{
	bool check[26];

	int N = getint();
	int K = getint();
	int Q = getint();

	for(int i = 1; i < Q; ++i) {
		while( is_numb(getchar()) ); // skip one integer
		getchar(); // skip one (P) character
		getchar(); // skip '\n'
	}

	for(int i = Q; i <= K; ++i) {
		int R = getint();
		check[getchar() - 'A'] = true;
		getchar(); // skip '\n'

		if(R == 0) {
			puts("-1");
			return 0;
		}
	}

	bool initial = true;
	for(int i = 1; i < N; ++i) {
		if(!check[i]) {
			if(initial) {
				initial = false;
			} else {
				putchar(' ');
			}
			putchar('A' + i);
		}
	}

	return 0;
}