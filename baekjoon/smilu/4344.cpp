#include <cstdio>

int main(void)
{
	int C, N, cnt, arr[1000];
	float sum;
	scanf("%d", &C);
	for(int c=0; c<C; ++c) {
		scanf("%d", &N);
		sum = cnt = 0;
		for(int i=0; i<N; ++i) {
			scanf("%d", arr + i);
			sum += arr[i];
		}
		sum /= N;
		for(int i=0; i<N; ++i) {
			if(arr[i] > sum) ++cnt;
		}
		printf("%.3f%%\n", 100.0 * cnt / N);
	}
}