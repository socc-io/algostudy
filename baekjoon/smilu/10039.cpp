#include <cstdio>

int sum, tmp;

int main(void)
{
	for(int i = 0; i < 5; ++i) {
		scanf("%d", &tmp);
		if(tmp < 40) tmp = 40;
		sum += tmp;
	}
	printf("%d", sum / 5);
}