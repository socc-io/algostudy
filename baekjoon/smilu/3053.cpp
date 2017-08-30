#include <cstdio>
#include <cmath>

int main(void)
{
	int R;
	scanf("%d", &R);
	R *= R;
	printf("%.6f\n%.6f", M_PI * R, 2. * R);
}