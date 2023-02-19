#include <bits/stdc++.h>
using namespace std;

struct Pt {
    double x;
    double y;
};

const double i_sqrt2 = 1.0 / sqrt(2.0);
const Pt dirs[8] = {
    {0, 1},
    {i_sqrt2, i_sqrt2},
    {1, 0},
    {i_sqrt2, -i_sqrt2},
    {0, -1},
    {-i_sqrt2, -i_sqrt2},
    {-1, 0},
    {-i_sqrt2, i_sqrt2},
};

bool cw(Pt a, Pt b, Pt c) {
  double op  = a.x*b.y + b.x*c.y + c.x*a.y;
         op -= a.y*b.x + b.y*c.x + c.y*a.x;
  return op < 0.0;
}

bool is_convex(const Pt *pts) {
    return cw(pts[0], pts[1], pts[2]) &&
        cw(pts[1], pts[2], pts[3]) &&
        cw(pts[2], pts[3], pts[4]) &&
        cw(pts[3], pts[4], pts[5]) &&
        cw(pts[4], pts[5], pts[6]) &&
        cw(pts[5], pts[6], pts[7]) &&
        cw(pts[6], pts[7], pts[0]) &&
        cw(pts[7], pts[0], pts[1]);
}

bool is_convex(const double *a) {
    Pt pts[8];
    for (int i = 0; i < 8; i++) {
        pts[i] = { dirs[i].x * a[i], dirs[i].y * a[i] };
    }
    return is_convex(pts);
}

int main() {
    int stat[8];
    for (int i = 0; i < 8; i++) {
        scanf("%d", &stat[i]);
    }

    int ans = 0;

    int order[8];
    double ordered_stat[8];
    iota(order, order + 8, 0);
    do {
        for (int i = 0; i < 8; i++) {
            ordered_stat[i] = stat[order[i]];
        }
        ans += is_convex(ordered_stat);
    } while (next_permutation(order, order + 8));

    printf("%d", ans);
}
