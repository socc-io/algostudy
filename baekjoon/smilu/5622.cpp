#include <cstdio>

const int cost[] = {3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7, 7, 8, 8, 8, 8, 9, 9, 9, 10, 10, 10, 10};

int main(void)
{
	int sum = 0;
	for(char ch = getchar(); 'A' <= ch && ch <= 'Z'; ch = getchar()) {
		sum += cost[ch - 'A'];
	}
	printf("%d", sum);
}