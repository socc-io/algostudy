#include <cstdio>

int main(void)
{
	int min = 0x7FFFFFFF;
	int max = -1;

	int N, tmp;
	scanf("%d", &N);
	for(int i=0; i<N; ++i) {
		scanf("%d", &tmp);
		if(tmp < min)
			min = tmp; 
		if(tmp > max)
			max = tmp;
	}

	printf("%d", min * max);

	return 0;
}