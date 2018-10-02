/*
 *Author: smilu97
 */

#include <cstdio>

typedef unsigned long long lld;

lld n, a;

int main(void)
{
    lld k = 0, v;

    scanf("%llu%llu", &n, &a);
    v = a;
    
    while (v <= n) {
        k += n / v;
        v *= a;
    }

    printf("%llu", k);

    return 0;
}
