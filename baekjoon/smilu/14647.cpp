#include <cstdio>
#include <cstring>

int N, M;

int col_cnt[500];
int row_cnt[500];
int all_cnt;
int tmp;

int main(void)
{
	scanf("%d%d", &N, &M);
	
	all_cnt = 0;
	memset(col_cnt, 0, sizeof(col_cnt));
	memset(row_cnt, 0, sizeof(row_cnt));
	for(int i=0; i<N; ++i) for(int j=0; j<M; ++j) {
		scanf("%d", &tmp);
		int nine_cnt = 0;
		while(tmp > 0) {
			if(tmp % 10 == 9) {
				nine_cnt++;
			}
			tmp /= 10;
		}
		row_cnt[i] += nine_cnt;
		col_cnt[j] += nine_cnt;
		all_cnt += nine_cnt;
	}

	int max_cnt = -1;
	for(int i=0; i<N; ++i) {
		if(max_cnt < row_cnt[i]) {
			max_cnt = row_cnt[i];
		}
	}
	for(int i=0; i<M; ++i) {
		if(max_cnt < col_cnt[i]) {
			max_cnt = col_cnt[i];
		}
	}

	printf("%d", all_cnt - max_cnt);
}