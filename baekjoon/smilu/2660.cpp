#include <cstdio>
#include <cstdlib>

#define INF 0xFFFFFF

int N;
int d[51][51];
int point[51];

int max(int a, int b) { return a > b ? a:b; }
int min(int a, int b) { return a < b ? a:b; }

int main(void)
{
	scanf("%d", &N);
	for(int i=0; i<N; ++i) for(int j=0; j<N; ++j) {
		d[i][j] = INF;
	}
	for(int i=0; i<N; ++i) d[i][i] = 0;
	for(;;) {
		int a, b;
		scanf("%d%d", &a, &b);
		if(a == -1 && b == -1) break;
		--a; --b;
		d[a][b] = 1;
		d[b][a] = 1;
	}
	for(int k=0; k<N; ++k) for(int i=0; i<N; ++i) for(int j=0; j<N; ++j) {
		int l = d[i][k] + d[k][j];
		if(l < d[i][j]) {
			d[i][j] = l;
		}
	}
	int min_point = INF;
	int min_idx = -1;
	for(int i=0; i<N; ++i) {
		point[i] = -1;
		for(int j=0; j<N; ++j) {
			point[i] = max(point[i], d[i][j]);
		}
		min_point = min(min_point, point[i]);
	}
	int count = 0;
	for(int i=0; i<N; ++i) {
		if(point[i] == min_point) ++count;
	}
	printf("%d %d\n", min_point, count);
	for(int i=0; i<N; ++i) {
		if(point[i] == min_point) {
			printf("%d ", i+1);
		}
	}
}