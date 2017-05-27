#include <cstdio>
#include <cstdlib>

#define INF 0xFFFFFF

int N, M;
int proj[101][101];
int bacon[101];

int main(void)
{
	scanf("%d%d", &N, &M);
	for(int i=0; i<N; ++i) for(int j=0; j<N; ++j) {
		proj[i][j] = INF;
	}
	for(int i=0; i<M; ++i) {
		int a, b;
		scanf("%d%d", &a, &b);
		proj[a-1][b-1] = 1;
		proj[b-1][a-1] = 1;
	}
	for(int k=0; k<N; ++k) {
		for(int i=0; i<N; ++i) {
			for(int j=0; j<N; ++j) {
				int l = proj[i][k] + proj[k][j];
				if(l < proj[i][j]) {
					proj[i][j] = l;
				}
			}
		}
	}
	int min_bacon = INF;
	int min_bacon_idx = -1;
	int bacon; 
	for(int i=0; i<N; ++i) {
		bacon = 0;
		for(int j=0; j<N; ++j) {
			bacon += proj[i][j];
		}
		bacon -= proj[i][i];
		if(bacon < min_bacon) {
			min_bacon = bacon;
			min_bacon_idx = i;
		}
	}
	printf("%d", min_bacon_idx+1);
}