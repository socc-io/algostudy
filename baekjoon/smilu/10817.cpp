#include <cstdio>

int main(void)
{
	int N[4];
	scanf("%d%d%d", N, N+1, N+2);
	printf("%d", N[0] < N[1] ? (N[1] < N[2] ? N[1] : N[0] < N[2] ? N[2] : N[0]) : (N[1] > N[2] ? N[1] : N[0] < N[2] ? N[0] : N[2]));
}