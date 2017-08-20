#include <cstdio>

int N;
int H[30000];
int M[30000];

int main(void)
{
	scanf("%d", &N);
	for(int i = 0; i < N; ++i) {
		scanf("%d", H + i);
	}

	int answer = 0;
	for(int i = N - 1; i >= 0 ; --i) {
		int h = H[i];
		int k = i + 1;
		while(k < N && H[k] < h) {
			k = M[k];
		}
		M[i] = k;

		if(answer < k - i - 1) {
			answer = k - i - 1;
		}
	}

	printf("%d", answer);

	return 0;
}