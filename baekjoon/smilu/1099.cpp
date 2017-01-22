#include <cstdio>
#include <cstring>
#include <algorithm>

#define INF 0x3FFFFFFF

#define SMILU_DEBUG

int dp[51];
char str[51];
int len_str;
char word[51][51];
int len_word[51];
int word_num;

int min(int a, int b)
{
	return a < b ? a : b;
}

int check(char* a, char* b, int l)
{
	char ab[51], bb[51];
	for(int i=0;i<l;++i) {
		ab[i] = a[i];
		bb[i] = b[i];
	}
	ab[l] = 0; bb[l] = 0;
	std::sort(ab, ab+l);
	std::sort(bb, bb+l);
	int res;
	if(!strcmp(ab, bb)) {
		res = 0;
		for(int i=0;i<l;++i) {
			if(a[i] != b[i]) ++res;
		}
	}
	else {
		res = -1;
	}
	#ifdef SMILU_DEBUG
	printf("a: %10s, b: %10s, l: %2d, res: %2d\n", ab, bb, l, res);
	#endif
	return res;
}

int main(void)
{
	// input
	gets(str);
	len_str = strlen(str);
	scanf("%d",&word_num);
	fflush(stdin);
	for(int i=0;i<word_num;++i) {
		gets(word[i]);
		len_word[i] = strlen(word[i]);
	}
	// check print
	#ifdef SMILU_DEBUG
	printf("str: %s (%d)\n", str, len_str);
	for(int i=0;i<word_num;++i) {
		printf("word%d: %s (%d)\n", i+1, word[i], len_word[i]);
	}
	#endif
	// dp initializing
	for(int i=0;i<=len_str;++i) dp[i] = INF;
	dp[0] = 0;
	// dp run
	for(int pos=0; pos<len_str; ++pos) {
		if(dp[pos] == INF) continue;
		int now_dp = dp[pos];
		char* strpos = str+pos;
		for(int word_idx=0; word_idx<word_num; ++word_idx) {
			int l_len_word = len_word[word_idx]; // now word length
			char* l_word = word[word_idx]; // now word
			if(pos + l_len_word > len_str) continue; // length check
			int check_res = check(strpos, l_word, l_len_word);
			if(check_res == -1) continue; // result check
			dp[pos+l_len_word] = min(dp[pos+l_len_word], now_dp + check_res); // update 
		}
	}
	// dp check print
	#ifdef SMILU_DEBUG
	for(int i=0;i<=len_str;++i) {
		printf("%2d ", i);
	} putchar('\n');
	for(int i=0;i<=len_str;++i) {
		printf("%2d ", dp[i] == INF ? -1 : dp[i]);
	} putchar('\n');
	#endif
	// res check and print
	int res = dp[len_str];
	printf("%d", res == INF ? -1 : res);
}