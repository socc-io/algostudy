#include <bits/stdc++.h>
using namespace std;

struct Environment {
    int h, n;
    vector< vector<bool> > lines;

    Environment(int h, int n):
        h(h), n(n),
        lines(h, vector<bool>(n-1, false))
        {}

    bool IsLine(int x, int y) const {
        if (IsLineOutBound(x, y)) return false;
        return lines[x][y];
    }

    bool IsLineOutBound(int x, int y) const {
        return x < 0 || x >= h || y < 0 || y >= n-1;
    }

    bool IsLinePlaceable(int x, int y) const {
        if (IsLineOutBound(x, y)) return false;

        return !IsLine(x, y) && !IsLine(x, y-1) && !IsLine(x, y+1);
    }

    void AddLine(int x, int y) {
        lines[x][y] = true;
    }

    void RemoveLine(int x, int y) {
        lines[x][y] = false;
    }

    vector<int> GetResults() const {
        vector<int> results(n);
        for (int i = 0; i < n; i++) results[i] = i;

        for (int i = 0; i < h; i++) {
            for (int j = 0; j < n-1; j++) {
                if (!IsLine(i, j)) continue;
                swap(results[j], results[j+1]);
            }
        }

        return results;
    }

    bool IsComplete() const {
        vector<int> results = GetResults();
        for (int i = 0; i < n; i++)
            if (results[i] != i)
                return false;
        return true;
    }

    bool FindCase(int cx, int cy, int put, int max_put) {
        if (put >= max_put) return IsComplete();
        if (cy >= n-1) return FindCase(cx+1, 0, put, max_put);
        if (cx >= h) return false;

        if (FindCase(cx, cy+1, put, max_put)) return true;

        if (IsLinePlaceable(cx, cy)) {
            AddLine(cx, cy);
            if (FindCase(cx, cy+1, put+1, max_put)) return true;
            RemoveLine(cx, cy);
        }

        return false;
    }

    int Solve() {
        if (IsComplete()) return 0;
        if (FindCase(0, 0, 0, 1)) return 1;
        if (FindCase(0, 0, 0, 2)) return 2;
        if (FindCase(0, 0, 0, 3)) return 3;
        return -1;
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m, h;
    cin >> n >> m >> h;

    Environment env(h, n);
    
    while (m--) {
        int x, y;
        cin >> x >> y;
        env.AddLine(x-1, y-1);
    }

    cout << env.Solve() << '\n';

    return 0;
}
