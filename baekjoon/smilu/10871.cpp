#include <cstdio>

int main(void)
{
	int N, X, tmp;
	scanf("%d%d", &N, &X);
	for(int i = 0; i < N; ++i) {
		scanf("%d", &tmp);
		if(tmp < X) {
			printf("%d ", tmp);
		}
	}
}