#include <cstdio>
#include <cstdlib>
#include <cstring>

void run(char* a, char* b)
{
	int a_len = strlen(a);
	int b_len = strlen(b);
	int cost  = 0;
	for(int cur=0; cur<a_len;) {
		int shouldPaste = true;
		for(int checker=0; checker<b_len; ++checker) {
			if (a[cur+checker] != b[checker]) {
				shouldPaste = false;
				break;
			}
		}
		cur += shouldPaste ? b_len : 1;
		++cost;
	}
	printf("%d\n", cost);
}

int main(void)
{
	int N;
	char a[10001];
	char b[101];
	scanf("%d", &N);
	for(int i=0;i<N;++i) {
		scanf("%s%s", a, b);
		run(a,b);
	}
	return 0;
}