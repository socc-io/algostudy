#include <cstdio>

int main(void)
{
	int a, b, v;
	scanf("%d%d%d", &a, &b, &v);

	printf("%d", (v-b-1) / (a-b) + 1);
}