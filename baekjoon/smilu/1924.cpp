#include <cstdio>

int x, y;

const char* days[] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};
const int day_sum[] = {0, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};

int main(void)
{
	scanf("%d%d", &x, &y);

	puts(days[(day_sum[x] + y) % 7]);

	return 0;
}