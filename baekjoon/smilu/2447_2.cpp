#include <bits/stdc++.h>
using namespace std;

void spaces(int n) {
    while (n--) putchar(' ');
}

void pline(int n, int l) {
    if (n == 1) {
        putchar('*');
        return;
    }
    int n3 = n / 3, n32 = (n3 << 1);
    if (n3 <= l && l < n32) {
        l -= n3;
        pline(n3, l);
        spaces(n3);
        pline(n3, l);
    } else {
        if (l >= n32) l -= n32;
        pline(n3, l);
        pline(n3, l);
        pline(n3, l);
    }
}

int main() {
    int n; scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        pline(n, i);
        putchar('\n');
    }
}
