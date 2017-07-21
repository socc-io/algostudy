#include <cstdio>

int N, M;
char tile[11][11];

int visited[100];
int match[100];

int left_cnt;
int right_cnt;

int left_able[100];
int right_able[100];

int offsets[6];

int try_match(int u)
{
	if(!left_able[u]) return 0;
	if(visited[u]) return 0;

	visited[u] = 1;

	int row = u % N;

	for(int offset_idx=(row == 0 ? 2 : 0); offset_idx<(row == N - 1 ? 4 : 6); ++offset_idx) {

		int v = u + offsets[offset_idx];

		if(v < 0 || v >= right_cnt) continue;
		if(!right_able[v]) continue;

		if(match[v] == -1 || try_match(match[v])) {
			match[v] = u;
			return 1;
		}
	}

	return 0;
}

void do_task()
{
	int dot_cnt = 0;

	scanf("%d%d", &N, &M);
	for(int i=0; i<N; ++i) {
		scanf("%s", tile[i]);
	}

	left_cnt = 0;
	for(int y=0; y<M; y+=2) {
		for(int x=0; x<N; ++x) {
			if(tile[x][y] == '.') {
				left_able[left_cnt++] = 1;
				dot_cnt++;
			} else {
				left_able[left_cnt++] = 0;
			}
		}
	}

	right_cnt = 0;
	for(int y=1; y<M; y+=2) {
		for(int x=0; x<N; ++x) {
			if(tile[x][y] == '.') {
				right_able[right_cnt++] = 1;
				dot_cnt++;
			} else {
				right_able[right_cnt++] = 0;
			}
		}
	}

	for(int i=0; i<right_cnt; ++i) {
		match[i] = -1;
	}

	offsets[0] = -N-1;
	offsets[1] = -1;
	offsets[2] = -N;
	offsets[3] = 0;
	offsets[4] = -N+1;
	offsets[5] = 1;

	int match_cnt = 0;
	for(int i=0; i<left_cnt; ++i) {
		for(int j=0; j<left_cnt; ++j) {
			visited[j] = 0;
		}
		match_cnt += try_match(i);
	}

	printf("%d\n", dot_cnt - match_cnt);
}

int main(void)
{
	int C;
	scanf("%d", &C);
	for(int i=0; i<C; ++i) {
		do_task();
	}
}