#include <bits/stdc++.h>
using namespace std;

const int dd[4][2] = {
    {1, 0}, {0, -1}, {-1, 0}, {0, 1},
};

struct Tile {
    vector< vector<bool> > pt;

    Tile(): pt(101, vector<bool>(101, false))
        {}

    bool OutBound(int x, int y) const {
        return x < 0 || x > 100 || y < 0 || y > 100;
    }

    void AddPoint(int x, int y) {
        if (OutBound(x, y)) return;
        pt[x][y] = true;
    }

    pair<int, int> AddCurve(int x, int y, int d, int g) {
        AddPoint(x, y);

        if (g == 0) {
            AddPoint(x + dd[d][0], y + dd[d][1]);
            return make_pair(x + dd[d][0], y + dd[d][1]);
        }

        auto e = AddCurve(x, y, d, g-1);

        int dx = e.first - x, dy = e.second - y;
        int nx = x + dx + dy, ny = y + dy - dx;
        AddCurve(nx, ny, (d+3)%4, g-1);

        return make_pair(nx, ny);
    }

    bool IsSquareFull(int x, int y) const {
        return pt[x][y] && pt[x+1][y] && pt[x][y+1] && pt[x+1][y+1];
    }
};

int main() {
    int n;
    cin >> n;

    Tile tile;
    
    while (n--) {
        int x, y, d, g;
        cin >> x >> y >> d >> g;
        tile.AddCurve(x, y, d, g);
    }

    int answer = 0;
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            answer += tile.IsSquareFull(i, j);
        }
    }
    cout << answer << '\n';
    
    return 0;
}
