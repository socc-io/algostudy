#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pi;

const int inf = 0x3f3f3f3f;

int n;
int ans[51];
int indices[51];
int dist[51];
pi ps[51];
int xs[51];
int ys[51];

void sort_indices() {
    iota(indices, indices + n, 0);
    sort(indices, indices + n, [&](int a, int b) {
        return dist[a] < dist[b];
    });
}

void update_dist(int cx, int cy) {
    for (int i = 0; i < n; i++) {
        int dx = abs(cx - ps[i].first);
        int dy = abs(cy - ps[i].second);
        dist[i] = dx + dy;
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> ps[i].first >> ps[i].second;
    }
    fill(ans, ans + n, inf);
    for (int xi = 0; xi < n; xi++) {
        int cx = ps[xi].first;
        for (int yi = 0; yi < n; yi++) {
            int cy = ps[yi].second;
            update_dist(cx, cy);
            sort_indices();
            int sum_dist = 0;
            for (int k = 0; k < n; k++) {
                sum_dist += dist[indices[k]];
                ans[k] = min(ans[k], sum_dist);
            }
        }
    }
    for (int i = 0; i < n; i++) cout << ans[i] << ' '; cout << '\n';
}
