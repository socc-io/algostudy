#include <iostream>
#include <algorithm>
using namespace std;

int N;
int A[50];
int B[50];

int main(void)
{
	scanf("%d", &N);

	for(int i=0; i<N; ++i) {
		scanf("%d", A + i);
	}
	for(int i=0; i<N; ++i) {
		scanf("%d", B + i);
	}

	sort(A, A + N);
	sort(B, B + N, [](const int a, const int b) {
		return a > b;
	});

	int sum = 0;
	for(int i=0; i<N; ++i) {
		sum += A[i] * B[i];
	}

	printf("%d", sum);
}
