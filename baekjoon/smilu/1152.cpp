#include <stdio.h>
#include <string.h>

int main(void)
{
	char str[1000001];
	int len;
	fgets(str, 1000001, stdin);
	len = strlen(str);
	int cnt = 0;
	bool switch_ = false;
	for(int i=0;i<len;++i) {
		char ch = str[i];
		if (ch == '\n') continue;
		if(!switch_ && ch != ' ') {
			switch_ = true;
			++cnt;
		}
		else if(switch_ && ch == ' ') {
			switch_ = false;
		}
	}
	printf("%d", cnt);
	return 0;
}