// 0 0 0 0 0 0 0
// 0 0 0 1 0 0 0
// 0 0 1 2 1 0 0
// 0 1 2 3 2 1 0
// 0 0 1 2 1 0 0
// 0 0 0 1 0 0 0
// 0 0 0 0 0 0 0


#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long ll;

int n, k;
ll tile[606][606];
ll area[606][606];

ll get_tile(int x, int y) {
    if (x < 0 || x >= n) return 0;
    if (y < 0 || y >= n) return 0;
    return tile[x][y];
}

ll get_area(int x, int y) {
    if (x < 0) return 0;
    if (y < 0) return 0;
    x = min(x, n-1);
    y = min(y, n-1);
    return area[x][y];
}

ll get_area_xyhw(int x, int y, int h, int w) {
    if (w <= 0) return 0;
    int x1 = x-1, y1 = y-1;
    int x2 = x+h-1, y2 = y+w-1;
    return get_area(x2, y2) - get_area(x1, y2) - get_area(x2, y1) + get_area(x1, y1);
}

ll get_left_top_area(int x, int y, int w) {
    int q = (w+1)>>1;
    return get_area_xyhw(x-q+1, y-q+1, q, q) +
        get_left_top_area(x, y-q, w-q);
        get_left_top_area(x-q, y, w-q);
}

ll get_left_bottom_area(int x, int y, int w) {
    int q = (w+1)>>1;
    return get_area_xyhw(x, y-q+1, q, q) +
        get_left_bottom_area(x-q, y, w-q);
        get_left_bottom_area(x, y+q, w-q);
}

ll get_right_top_area(int x, int y, int w) {
    int q = (w+1)>>1;
    return get_area_xyhw(x-q+1, y, q, q) +
        get_right_top_area(x, y+q, w-q);
        get_right_top_area(x-q, y, w-q);
}

ll get_right_bottom_area(int x, int y, int w) {
    int q = (w+1)>>1;
    return get_area_xyhw(x, y, q, q) +
        get_right_bottom_area(x+q, y, w-q);
        get_right_bottom_area(x, y+q, w-q);
}

ll get_left_dia_area(int x, int y, int w) {
    int q = (w+1)>>1;
    return get_area_xyhw(x-q+1, y-q+1, (q<<1)-1, q) + 
        get_left_dia_area(x, y-q, w-q) +
        get_left_top_area(x-q, y, w-q) +
        get_left_bottom_area(x+q, y, w-q);
}

ll get_right_dia_area(int x, int y, int w) {
    int q = (w+1)>>1;
    return get_area_xyhw(x, y-q+1, (q<<1)-1, q) + 
        get_right_dia_area(x, y+q, w-q) +
        get_right_top_area(x-q, y, w-q) +
        get_right_bottom_area(x+q, y, w-q);
}

ll get_right_offset(int x, int y, int w) {
    return get_right_dia_area(x, y+1, w) - get_left_dia_area(x, y, w);
}

ll get_diamond_area(int x, int y, int w) {
    return get_left_dia_area(x, y, w) + get_right_dia_area(x, y+1, w-1);
}

ll get_shotgun_area(int x, int y, int w) {
    ll res = 0;
    for (int i = 0; i < w; i++) {
        res += get_diamond_area(x, y, i+1);
    }
    return res;
}

void solve(int tc) {
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> tile[i][j];
        }
    }

    area[0][0] = tile[0][0];
    for (int i = 1; i < n; i++) {
        area[i][0] = area[i-1][0] + tile[i][0];
        area[0][i] = area[0][i-1] + tile[0][i];
    }
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            area[i][j] = area[i-1][j] + area[i][j-1] - area[i-1][j-1] + tile[i][j];
        }
    }
    ll max_area = 0;
    for (int x = 0; x < n; x++) {
        ll area = get_shotgun_area(x, 0, k);
        max_area = max(max_area, area);
        for (int y = 1; y < n; y++) {
            area += get_right_offset(x, y-1, k);
            max_area = max(max_area, area);
        }
    }
    cout << "Case #" << tc+1 << endl;
    cout << max_area << endl;
}

int main() {
    setbuf(stdout, NULL);
    int t; cin >> t;
    for (int i = 0; i < t; i++) {
        solve(i);
    }
    return 0;
}
