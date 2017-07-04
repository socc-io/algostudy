#include <cstdio>

int main(void)
{
	int l, r;
	int first, tmp;
	scanf("%d", &first);

	if (first < 10) first *= 10;

	l = first / 10;
	r = first % 10;

	int first_l = l;
	int first_r = r;

	int cnt = 0;
	do {
		tmp = r;
		r = l + r;
		if (r >= 10) r -= 10;
		l = tmp;

		++cnt;
	} while(l != first_l || r != first_r);

	printf("%d", cnt);

	return 0;
}