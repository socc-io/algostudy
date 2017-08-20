#include <cstdio>

int N;
int A[50];
int B[50];
int K[50];

int main(void)
{
	int tmp;

	scanf("%d", &N);
	for(int i = 0; i < N; ++i) {
		scanf("%d", A + i);
		K[i] = i;
	}

	for(int i = 0; i < N - 1; ++i) {
		for(int j = 0; j < N - 1 - i; ++j) {
			if(A[K[j]] > A[K[j + 1]]) {
				tmp = K[j];
				K[j] = K[j + 1];
				K[j + 1] = tmp;
			}
		}
	}

	// printf("K: ");
	// for(int i = 0; i < N; ++i) {
	// 	printf("%d ", K[i]);
	// } printf("\n");

	for(int i = 0; i < N; ++i) {
		B[K[i]] = i;
	}

	// printf("B: ");
	for(int i = 0; i < N; ++i) {
		printf("%d ", B[i]);
	} printf("\n");

	return 0;
}