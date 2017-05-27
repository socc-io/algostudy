#include <cstdio>
#include <cstdlib>
#include <algorithm>

int length, num; // L, C
char ch[16]; // characters
char buffer[16];
int isVowel[16]; // isVowel[i] would be 1 if ch[i] is vowel
int vowelCount; 

const int vowelCountMin = 1;
int vowelCountMax; // length - 2

const char* vowels = "aeiou";

void dfs(int pos, int start)
{
	if(pos >= length) { // check this is leaf node
		if(vowelCountMax < vowelCount) return;
		if(vowelCount < vowelCountMin) return;
		printf("%s\n", buffer);
		return;
	}
	int next_pos = pos + 1;
	int end      = pos + num - length;
	for(int i=start; i<=end; ++i) {
		buffer[pos] = ch[i];
		vowelCount += isVowel[i];
		dfs(next_pos, i+1);
		vowelCount -= isVowel[i];
	}
}

int main(void)
{
	scanf("%d%d", &length, &num); // get input
	vowelCountMax = length - 2;
	buffer[length] = '\0';
	for(int i=0; i<num; ++i) {
		scanf("%s", buffer);
		ch[i] = buffer[0];
	}

	std::sort(ch, ch+num); // sort alphabetically

	for(int i=0; i<num; ++i) { // check every char if it is vowel
		isVowel[i] = 0;
		for(int j=0; j<5; ++j) {
			if(vowels[j] == ch[i]) {
				isVowel[i] = 1;
				break;
			}
		}
	}

	// printf("ch: %s\n", ch);

	vowelCount = 0;
	dfs(0, 0);
	return 0;
}