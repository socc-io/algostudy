#include <cstdio>

int main()
{
    int a, m, v, r = 1;
    
    scanf("%d%d", &a, &m);
    v = a % m;
    while (v != 1) {
        v = (v + a) % m;
        ++r;
    }
    printf("%d", r);
}