#include <cstdio>
#include <cstring>

const char chars[8][4] = {"c=", "c-", "dz=", "d-", "lj", "nj", "s=", "z="};
const int chars_len[8] = {2, 2, 3, 2, 2, 2, 2, 2};

char buf[101];
int len, same_cnt;

int main(void)
{
	scanf("%s", buf);
	len = strlen(buf);
	for(int i = 0; i < len; ++i) { 
		for(int j = 0; j < 8; ++j) {
			if(i + chars_len[j] > len) continue;
			bool same = true;
			for(int k = 0; k < chars_len[j]; ++k) {
				if(buf[i + k] != chars[j][k]) {
					same = false; 
					break;
				}
			}
			if(same) {
				same_cnt += chars_len[j] - 1;
				i += chars_len[j] - 1;
				break;
			}
		}
	}
	printf("%d", len - same_cnt);
}