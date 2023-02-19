#include <bits/stdc++.h>
using namespace std;

int w, h, bx, by, p;
int r;

bool check_left(int x, int y) {
    y -= r;
    return x*x + y*y <= r*r;
}

bool check_right(int x, int y) {
    x -= w;
    y -= r;
    return x*x + y*y <= r*r;
}

bool check_mid(int x, int y) {
    return 0 <= y && y <= h;
}

bool check(int x, int y) {
    x -= bx;
    y -= by;

    if (x < 0) return check_left(x, y);
    else if (x < w) return check_mid(x, y);
    else return check_right(x, y);
}

int main() {
    scanf("%d %d %d %d %d", &w, &h, &bx, &by, &p);
    r = h;

    w *= 2;
    h *= 2;
    bx *= 2;
    by *= 2;

    int count = 0;
    while (p--) {
        int x, y;
        scanf("%d %d", &x, &y);
        count += check(2*x, 2*y);
    }
    printf("%d", count);
}
