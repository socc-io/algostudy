#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pi;
typedef vector<int> vi;
typedef vector<vi> vvi;

const int inf = 0x3f3f3f3f;
const int dd[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};

int n, m, k, l;
int tile[22][10100];
pi merch_pos[110];
int sched[220];

bool in_range(pi x) {
    return 0 <= x.first && x.first < n && 0 <= x.second && x.second < m;
}

bool available(pi x) {
    if (!in_range(x)) return false;
    return tile[x.first][x.second] != -1;
}

int get_dist_matrix(pi src, int dst_land) {
   vvi dist(n, vi(m, inf));
   queue<pi> q;
   q.push(src);
   dist[src.first][src.second] = 0;
   if (tile[src.first][src.second] == dst_land) return 0;
   while (!q.empty()) {
       pi u = q.front(); q.pop();
       int vd = dist[u.first][u.second] + 1;
       for (int di = 0; di < 4; di++) {
           int nx = u.first + dd[di][0];
           int ny = u.second + dd[di][1];
           pi v = make_pair(nx, ny);
           if (!available(v)) continue;
           if (dist[nx][ny] != inf) continue;
           if (tile[nx][ny] == dst_land) return vd;
           dist[nx][ny] = vd;
           q.push(v);
       }
   }
   return inf;
}

int solve() {
    int sum_cost = 0;
    pi cur = make_pair(0, 0);
    for (int i = 0; i < l; i++) {
        int cost = get_dist_matrix(cur, sched[i]);
        if (cost == inf) return -1;
        sum_cost += cost + 1;
        // cout << "cost: " << cost << '\n';
        cur = merch_pos[sched[i] - 1];
    }
    return sum_cost;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m >> k;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> tile[i][j];
        }
    }
    for (int i = 0; i < k; i++) {
        cin >> merch_pos[i].first >> merch_pos[i].second;
        --merch_pos[i].first;
        --merch_pos[i].second;
    }
    cin >> l;
    for (int i = 0; i < l; i++) {
        cin >> sched[i];
    }

    cout << solve() << '\n';
}
