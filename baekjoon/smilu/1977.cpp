#include <cstdio>
#include <cmath>

inline int square_sum(int v)
{
	return v * (v + 1) * (2 * v + 1) / 6;
}

int main(void)
{
	int min, max;
	scanf("%d%d", &min, &max);

	int s_min = ceil(sqrt(min));
	int s_max = floor(sqrt(max));

	if (s_min <= s_max)
		printf("%d\n%d\n", square_sum(s_max) - square_sum(s_min - 1), s_min * s_min);
	else
		printf("-1");
}