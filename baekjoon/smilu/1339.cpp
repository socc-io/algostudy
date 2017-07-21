#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int N;

char S[10][9];
int S_len[10];

int weight[26];
int sorted[26];

bool sorter(const int a, const int b)
{
	return weight[a] > weight[b];
}

int main(void)
{
	scanf("%d", &N);
	for(int i=0; i<N; ++i) {
		scanf("%s", S[i]);
		S_len[i] = strlen(S[i]);
	}

	for(int i=0; i<N; ++i) {
		int w = 1;
		for(int j=0; j<S_len[i]; ++j) {
			weight[S[i][S_len[i]-1-j] - 'A'] += w;
			w *= 10;
		}
	}

	for(int i=0; i<26; ++i) {
		sorted[i] = i;
	}

	sort(sorted, sorted + 26, sorter);
	
	int res = 0;
	for(int i=0; i<10; ++i) {
		if(weight[sorted[i]] <= 0) break;
		res += (9 - i) * weight[sorted[i]];
	}

	printf("%d", res);
}