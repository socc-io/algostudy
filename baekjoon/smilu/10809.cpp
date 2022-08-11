#include <iostream>
#include <cstring>
using namespace std;

int main(void)
{
	int pos[26];
	char s[101];

	pos[3] = 0;

	cin >> s;

	memset(pos, -1, sizeof(int) * 26);
	for(int i=0; s[i] != '\0'; ++i) {
		int key = s[i] - 'a';
		if(pos[key] == -1) {
			pos[key] = i;
		}
	}

	for(int i=0; i<26; ++i) {
		cout << pos[i] << ' ';
	}
}
