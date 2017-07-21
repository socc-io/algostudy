#include <iostream>
#include <cstring>
using namespace std;

int main(void)
{
	int pos[26];
	char s[101];

	scanf("%s", s);

	memset(pos, -1, sizeof(int) * 26);
	for(int i=0; s[i] != '\0'; ++i) {
		if(pos[s[i] - 'a'] == -1) {
			pos[s[i] - 'a'] = i;
		}
	}

	for(int i=0; i<26; ++i) {
		printf("%d ", pos[i]);
	}
}