#include <cstdio>

#define INF (0x7FFFFFFF)

struct Word
{
	int char_cnt[26];
	int len;
	Word() {
		for(int i=0; i<26; ++i)
			char_cnt[i] = 0;
		len = 0;
	}
	void add_char(char ch)
	{
		int idx = ch - 'a';
		if(0 <= idx && idx < 26) {
			char_cnt[idx]++;
		}
		len++;
	}
	void from_string(char* s)
	{
		for(char* ch = s; (*ch) != '\0'; ++ch) {
			add_char(*ch);
		}
	}
	bool operator==(const Word &b)
	{
		for(int i=0; i<26; ++i) {
			if(char_cnt[i] != b.char_cnt[i]) {
				return 0;
			}
		}
		return 1;
	}
};

int string_distance(char* a, char* b, int len)
{
	int distance = 0;
	for(int i=0; i<len; ++i) {
		if(a[i] != b[i])
			distance++;
	}
	return distance;
}

int N;
char full_string[51];
char vanila_words[50][51];

Word words[50];

int cs_mem[50];

int calculate_string(char* s)
{
	if(*s == '\0') return 0;

	int mem_idx = s - full_string;
	if(cs_mem[mem_idx] != -1) {
		return cs_mem[mem_idx];
	}

	Word word_cur;

	int min_cost = INF;

	for(char* ch=s; (*ch) != '\0'; ++ch) {
		word_cur.add_char(*ch);
		for(int i=0; i<N; ++i) {
			if(word_cur == words[i]) {
				int cost = calculate_string(ch + 1);
				if(cost != INF) {
					cost += string_distance(vanila_words[i], s, word_cur.len);
					if(cost < min_cost) {
						min_cost = cost;
					}
				}
			}
		}
	}

	cs_mem[mem_idx] = min_cost;

	return min_cost;
}

int main(void)
{
	scanf("%s%d", full_string, &N);
	for(int i=0; i<N; ++i) {
		scanf("%s", vanila_words[i]);
		words[i].from_string(vanila_words[i]);
	}

	for(int i=0; i<50; ++i) {
		cs_mem[i] = -1;
	}

	int cost = calculate_string(full_string);

	printf("%d", cost == INF ? -1 : cost);
}