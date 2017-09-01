#include <cstdio>

int a, b;
char c[102];

int main(void)
{
    scanf("%d%d%s", &a, &b, c);
    char *ch = c;
    for(;*ch != '\0'; ++ch) {}
    printf("%d", (*(ch-1) - '0') & 1 ? a^b : a);
}
