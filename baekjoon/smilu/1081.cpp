#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll pc[10];

ll sub(ll u, int p, int x) {
    const int up = (u / pc[p]) % 10;
    if (x < up) {
        return (u / pc[p+1] + 1) * pc[p];
    } else if (x == up) {
        return (u / pc[p+1]) * pc[p] + u % pc[p] + 1;
    } else {
        return (u / pc[p+1]) * pc[p];
    }
}

int main() {
    int l, u;
    scanf("%d %d", &l, &u);
    
    pc[0] = 1;
    for (int i = 1; i < 10; i++) pc[i] = pc[i-1] * 10;

    ll ans = 0;
    for (int i = 0; i < 10; i++) {
        for (int j = 1; j < 10; j++) {
            ans += (sub(u, i, j) - sub(l-1, i, j)) * j;
        }
    }

    printf("%lld", ans);
}
