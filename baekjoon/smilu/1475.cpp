#include <cstdio>

int main(void)
{
	int n;
	scanf("%d", &n);

	int count[10] = {0};
	while(n) {
		count[n % 10]++;
		n /= 10;
	}
	count[6] += count[9];
	count[6] = (count[6] + 1) / 2;
	count[9] = 0;

	int max = -1;
	for(int i=0; i<10; ++i) {
		if(count[i] > max) {
			max = count[i];
		}
	}

	printf("%d", max);
}