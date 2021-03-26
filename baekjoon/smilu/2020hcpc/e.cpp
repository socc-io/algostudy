#include <bits/stdc++.h>
using namespace std;

int n, m;
int tile[1515][1515];
int s_row[1515][1515];
int s_col[1515][1515];

void solve(int x, int y, int p) {
    int right = upper_bound(s_row[x], s_row[x] + n+1, s_row[x][y] + p) - (s_row[x] + y) - 1;
    int left  = (s_row[x] + y + 1) - lower_bound(s_row[x], s_row[x] + n+1, s_row[x][y+1] - p);
    
    int down  = upper_bound(s_col[y], s_col[y] + n+1, s_col[y][x] + p) - (s_col[y] + x) - 1;
    int up    = (s_col[y] + x + 1) - lower_bound(s_col[y], s_col[y] + n+1, s_col[y][x+1] - p);

    // printf("(%d, %d, %d, %d)\n", right, left, up, down);

    int res = max(max(left, right), max(up, down));
    if (res == 0) cout << "Silver Pantheon\n";
    else cout << res << '\n';
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> tile[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 1; j <= n; j++) {
            s_row[i][j] = s_row[i][j-1] + tile[i][j-1];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 1; j <= n; j++) {
            s_col[i][j] = s_col[i][j-1] + tile[j-1][i];
        }
    }

    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j <= n; j++) {
    //         printf("%2d ", s_row[i][j]);
    //     } puts("");
    // } puts("");
    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j <= n; j++) {
    //         printf("%2d ", s_col[i][j]);
    //     } puts("");
    // }
    
    for (int i = 0; i < m; i++) {
        int x, y, p; cin >> x >> y >> p;
        solve(y-1, x-1, p);
    }
}