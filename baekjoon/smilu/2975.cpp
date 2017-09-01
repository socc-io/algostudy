#include <cstdio>

int main(void)
{
    int a, b;
    char m;
    while(1) {
        scanf("%d", &a);
        getchar(); m = getchar(); getchar();
        scanf("%d", &b);
        if(a == 0 && m == 'W' && b == 0) break;
        if(m == 'W') a -= b;
        else a += b;
        if(a < -200) puts("Not allowed");
        else printf("%d\n", a);
    }
}
