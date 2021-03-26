#include <bits/stdc++.h>
using namespace std;

double x, y, D, T, d;

double try_k(double k) {
    if (k < 0) return try_k(0);
    return k*T + abs(d - k*D);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0); 
    cin >> x >> y >> D >> T;
    d = sqrt(x*x + y*y);
    double k = floor(d/D);
    double ans = d;
    if (D > T) {
        ans = min(ans, try_k(k-1));
        ans = min(ans, try_k(k));
        ans = min(ans, try_k(k+1));
        if (k >= 1) ans = min(ans, (k+1)*T);
    }
    printf("%.13lf\n", ans);
}
