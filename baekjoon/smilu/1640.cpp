#include <bits/stdc++.h>
using namespace std;

int n, m;
char tile[1010][1010];
int row[1010];
int col[1010];

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> tile[i];
        for (int j = 0; j < m; j++) {
            row[i] += tile[i][j] - '0';
            col[j] += tile[i][j] - '0';
        }
    }
    int a = 0, b = 0;
    for (int i = 0; i < n; i++) a += row[i] & 1;
    for (int i = 0; i < m; i++) b += col[i] & 1;
    if ((a&1) != (b&1)) {
        puts("-1");
        return 0;
    }
    if (!(a&1)) cout << min(a+b, n+m-a-b) << '\n';
    else cout << min(n-a+b, m-b+a) << '\n';
}
