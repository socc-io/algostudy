#include <bits/stdc++.h>
using namespace std;

double x, y, d, t;

int main() {
    scanf("%lf %lf %lf %lf", &x, &y, &d, &t);
    double l2 = hypot(x, y);
    double n_less = floor(l2 / d);
    double n_more = ceil(l2 / d);

    double ans = l2;
    ans = min(ans, n_less*t + abs(l2 - d*n_less));
    ans = min(ans, n_more*t + abs(l2 - d*n_more));
    ans = min(ans, max(2.0, n_more) * t);
    
    printf("%.9lf", ans);
}
