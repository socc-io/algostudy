#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct Line {
    ll from;
    ll to;
    bool operator<(const Line &l) const {
        if (from != l.from) return from < l.from;
        return to < l.to;
    }
    bool including(ll x) const {
        return from <= x && x <= to;
    }
    ll length() const {
        return to - from;
    }
};

struct LineSet {
    vector<Line> lines;
    void add(Line new_line) {
        if (lines.size() == 0) {
            lines.push_back(new_line);
            return;
        }

        Line & last_line = lines[lines.size() - 1];
        if (last_line.including(new_line.from)) {
            last_line.to = max(last_line.to, new_line.to);
        } else {
            lines.push_back(new_line);
        }
    }
    ll length() const {
        ll sum = 0;
        for (const auto & line: lines) {
            sum += line.length();
        }
        return sum;
    }
};

int n, m;
Line lines[1000000];

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> lines[i].from >> lines[i].to;
        if (lines[i].from <= lines[i].to) {
            --i;
            --n;
        } else {
            lines[i].from = m - lines[i].from;
            lines[i].to = m - lines[i].to;
        }
    }
    sort(lines, lines + n);
    LineSet s;
    for (int i = 0; i < n; i++) {
        s.add(lines[i]);
    }
    cout << m + (s.length() << 1) << '\n';
}
