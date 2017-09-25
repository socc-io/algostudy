#include <cstdio>

int main(void)
{
    int a, b, cnt=0;
    scanf("%*d%d%d", &a, &b);
    for(; a != b; ++cnt) {
        a = (a-1)/2+1;
        b = (b-1)/2+1;
    }
    printf("%d", cnt);
}
