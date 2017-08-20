#include <cstdio>

int cnt[26];

int main(void)
{
	char ch;
	while(~(ch = getchar())) {
		if(ch >= 'a') ch -= 'a';
		else ch -= 'A';
		++cnt[ch];
	}
	int max_val = cnt[0];
	int max_idx = 0;
	int max_cnt = 1;
	for(int i = 1; i < 26; ++i) {
		if(max_val < cnt[i]) {
			max_val = cnt[i];
			max_idx = i;
			max_cnt = 1;
		} else if(max_val == cnt[i]) {
			++max_cnt;
		}
	}
	putchar(max_cnt == 1 ? 'A' + max_idx : '?');
}