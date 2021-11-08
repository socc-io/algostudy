#include <stdio.h>

inline int sqr(int x) { return x*x; }

inline int abs(int x) { return x * ((x > 0) - (x < 0)); }

inline int gcd(int a, int b) {
    int tmp;
    if (a < b)  {
        tmp = a;
        a = b;
        b = tmp;
    }
    while (b) {
        tmp = a % b;
        a = b; b = tmp;
    }
    return a;
}

int main() {
    int buf[200], bl = 0;
    int n, a, b;
    scanf("%d %d %d", &n, &a, &b);
    int g = abs(b - a);
    n -= 2;
    while (n--) {
        scanf("%d", &b);
        g = gcd(g, abs(b - a));
    }
    for (a = 2; a*a <= g; a++) if (!(g % a)) {
        printf("%d ", a);
        buf[bl++] = g / a;
    }
    bl -= (bl > 0 && sqr(buf[bl - 1]) == g);
    while (bl--) printf("%d ", buf[bl]);
    printf("%d", g);
}
