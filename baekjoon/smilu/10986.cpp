#include <bits/stdc++.h>
using namespace std;

int c[1000];

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int s = 0;
    c[0] = 1;
    for (int i = 0; i < n; i++) {
        int a;
        scanf("%d", &a);
        s = (s + a) % m;
        c[s]++;
    }

    long long ans = 0;
    for (int i = 0; i < m; i++) {
        long long t = c[i];
        ans += (t * (t-1)) >> 1;
    }
    printf("%lld", ans);
}
