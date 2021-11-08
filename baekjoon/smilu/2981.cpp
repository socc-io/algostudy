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
        int tmp; scanf("%d", &tmp);
        g = gcd(g, abs(tmp - a));
    }
    for (int i = 2; i*i <= g; i++) if (!(g % i)) {
        printf("%d ", i);
        buf[bl++] = g / i;
    }
    bl -= (bl > 0 && sqr(buf[bl - 1]) == g);
    while (bl--) printf("%d ", buf[bl]);
    printf("%d", g);
}
