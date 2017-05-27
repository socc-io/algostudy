#include <cstdio>
#include <cstdlib>

#define INF 0xFFFFFF

int N, M; 
int d[100][100];

int min(int a, int b){
	return a<b ? a:b;
}

int main(void)
{
	scanf("%d%d", &N, &M);
	for(int i=0; i<N; ++i) for(int j=0; j<N; ++j) {
		d[i][j] = INF;
	}
	for(int i=0; i<N; ++i) d[i][i] = 0;
	for(int i=0; i<M; ++i) {
		int from, to, cost;
		scanf("%d%d%d", &from, &to, &cost);
		--from; --to;
		d[from][to] = min(d[from][to], cost);
	}
	for(int k=0; k<N; ++k) for(int i=0; i<N; ++i) for(int j=0; j<N; ++j) {
		int l = d[i][k] + d[k][j];
		if(l < d[i][j]) {
			d[i][j] = l;
		}
	}
	for(int i=0; i<N; ++i) {
		for(int j=0; j<N; ++j) {
			printf("%d ", d[i][j] == INF ? 0 : d[i][j]);
		}
		printf("\n");
	}
}