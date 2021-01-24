#include <bits/stdc++.h>
using namespace std;

struct Line {
    int from;
    int to;
    bool operator<(const Line &l) const {
        if (from != l.from) return from < l.from;
        return to < l.to;
    }
    bool including(int x) const {
        return from <= x && x <= to;
    }
    int length() const {
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
    int length() const {
        int sum = 0;
        for (const auto & line: lines) {
            sum += line.length();
        }
        return sum;
    }
};

int n;
Line lines[1000000];

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> lines[i].from >> lines[i].to;
    }
    sort(lines, lines + n);
    LineSet s;
    for (int i = 0; i < n; i++) {
        s.add(lines[i]);
    }
    cout << s.length() << '\n';
}
