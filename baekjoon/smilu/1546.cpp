#include <cstdio>

int main(void)
{
	float sum = 0;
	int N, tmp, max = -1;
	scanf("%d", &N);
	for(int i = 0; i < N; ++i) {
		scanf("%d", &tmp);
		sum += tmp;
		if(max < tmp) {
			max = tmp;
		}
	}
	printf("%.2f", sum / N / max * 100);
}