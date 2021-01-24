#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int n, m;
char tile[111][111];
ll sum[111][111];

ll area(int x1, int x2, int y1, int y2) {
    return sum[x1][y1] + sum[x2][y2] - sum[x1][y2] - sum[x2][y1];
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m;
    for (int i = 0; i < n; i++) cin >> tile[i];

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            sum[i][j] = sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1] + tile[i-1][j-1] - '0';
        }
    }

    ll ans = 0, mul;

    for (int i = 1; i < m; i++) {
        for (int j = i+1; j < m; j++) {
            mul = area(0, n, 0, i) * area(0, n, i, j) * area(0, n, j, m);
            ans = max(ans, mul);
        }
    }

    for (int i = 1; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            mul = area(0, i, 0, m) * area(i, j, 0, m) * area(j, n, 0, m);
            ans = max(ans, mul);
        }
    }

    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m; j++) {
            mul = area(0, i, 0, m) * area(i, n, 0, j) * area(i, n, j, m); // top full
            ans = max(ans, mul);
            mul = area(i, n, 0, m) * area(0, i, 0, j) * area(0, i, j, m); // bottom full
            ans = max(ans, mul);
            mul = area(0, i, 0, j) * area(i, n, 0, j) * area(0, n, j, m); // right full
            ans = max(ans, mul);
            mul = area(0, n, 0, j) * area(0, i, j, m) * area(i, n, j, m); // left full
            ans = max(ans, mul);
        }
    }

    cout << ans << '\n';
}
