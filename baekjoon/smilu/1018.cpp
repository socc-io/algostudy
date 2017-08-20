#include <cstdio>
#include <cstdlib>

int M, N;
bool board[50][50];

char s_tmp[100];

inline int min(int a, int b)
{
	if(a < b) return a;
	return b;
}

inline int get_cost(int x, int y)
{
	int cnt[2][2] = {0, 0, 0, 0};

	int f = 0;
	for(int i = x; i < x + 8 ; ++i) {
		f = i % 2;
		for(int j = y; j < y + 8; ++j) {
			++cnt[f][board[i][j]];
			f = 1 - f;
		}
	}

	return min(cnt[0][1] + cnt[1][0], cnt[0][0] + cnt[1][1]);
}

int main(void)
{
	scanf("%d%d", &M, &N);
	for(int i = 0; i < M; ++i) {
		scanf("%s", s_tmp);
		for(int j = 0; j < N; ++j) {
			board[i][j] = s_tmp[j] == 'W';
		}
	}

	int min = 99999;
	for(int i = 0; i <= M - 8; ++i) {
		for(int j = 0; j <= N - 8; ++j) {
			int tmp = get_cost(i, j);
			if(tmp < min) {
				min = tmp;
			}
		}
	}

	printf("%d", min);

	return 0;
}