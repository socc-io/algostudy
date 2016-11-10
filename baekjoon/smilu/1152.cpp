#include <stdio.h>
#include <string.h>

int main(void)
{
	char str[1000000];
	int len;
	fgets(str, 1000000, stdin);
	len = strlen(str);
	if(len<2) {
		printf("0");
		return 0;
	}
	int cnt = 0;
	for(int i=0;i<len;++i) {
		if(str[i] == ' ') {
			cnt++;
		}
	}
	printf("%d", cnt + 1);
	return 0;
}