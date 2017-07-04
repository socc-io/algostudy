#include <cstdio>

int main(void)
{
	int x, y, w, h;
	scanf("%d%d%d%d", &x, &y, &w, &h);

	int r = x;
	if (r > w - x)
		r = w - x;
	if (r > y)
		r = y;
	if (r > h - y)
		r = h - y;

	printf("%d", r);

	return 0;
}