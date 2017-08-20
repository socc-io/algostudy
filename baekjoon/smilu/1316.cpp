#include <cstdio>
#include <cstring>

int N, cnt;
bool check[26];

int main(void)
{
	for(scanf("%d", &N), getchar(); N; N--) {
		memset(check, 0, sizeof(check));
		char prev = 0;
		bool succ = true;
		for(char ch = getchar(); 'a' <= ch && ch <= 'z'; ch = getchar()) {
			if(!succ) continue;
			if(check[ch - 'a'] && prev && prev != ch) {
				succ = false;
			}
			prev = ch;
			check[ch - 'a'] = true;
		}
		if(succ) ++cnt;
	}
	printf("%d", cnt);
}