#include <cstdio>
#include <cstdlib>

int M, N, K;
int tile[50][50];

void burn(int x, int y)
{
	if(x < 0 || y < 0) return;
	if(x >= M || y >= N) return;
	if(tile[x][y] == 0) return;
	tile[x][y] = 0;
	burn(x-1,y);
	burn(x+1,y);
	burn(x,y-1);
	burn(x,y+1);
}

void run()
{
	scanf("%d%d%d", &M, &N, &K);
	for(int i=0; i<M; ++i) {
		for(int j=0; j<N; ++j) {
			tile[i][j] = 0;
		}
	}
	for(int i=0; i<K; ++i) {
		int x, y;
		scanf("%d%d", &x, &y);
		tile[x][y] = 1;
	}
	int cnt = 0;
	for(int i=0; i<M; ++i) {
		for(int j=0; j<N; ++j) {
			if(tile[i][j] == 1) {
				++cnt;
				burn(i, j);
			}
		}
	}
	printf("%d\n", cnt);
}

int main(void)
{
	int T;
	scanf("%d", &T);
	for(int i=0; i<T; ++i) {
		run();
	}
	return 0;
}