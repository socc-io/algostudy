#include <cstdio>

int next[1000];

int N, M;

int main(void)
{
	scanf("%d%d", &N, &M);
	for(int i = 0; i < N - 1; ++i) {
		next[i] = i + 1;
	}
	next[N - 1] = 0;

	int ccur = (N + M - 2) % N;
	int cur = M - 1;
	int idx = 0;

	printf("<");
	for(; idx < N; ++idx) {
		printf("%d", cur + 1);
		if(idx < N - 1) printf(", ");
		next[ccur] = next[cur];
		for(int i = 0; i < M; ++i) {
			cur = next[cur];
			if(i != 0) ccur = next[ccur];
		}
	}
	printf(">");
}