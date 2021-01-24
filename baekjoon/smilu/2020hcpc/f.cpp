#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pi;
typedef priority_queue<pi, vector<pi>, greater<pi>> pq;

const int inf = 0x3f3f3f3f;

int n, m, k, s, g;
vector<int> bases;
vector<int> camps;
vector<pi> edges[1010];

vector<int> dijkstra_1() {
    vector<int> dist(n, inf);
    vector<bool> visit(n, false);
    vector<pi> bk(n, {-1, -1});
    pq q;
    dist[s] = 0;
    q.push(make_pair(0, s));
    while (!q.empty()) {
        int u = q.top().second; q.pop();
        if (visit[u]) continue;
        visit[u] = true;
        for (int i = 0; i < edges[u].size(); i++) {
            pi e = edges[u][i];
            int v = e.first;
            int cost = e.second;
            int vd = dist[u] + cost * 2;
            if (vd < dist[v]) {
                dist[v] = vd;
                bk[v] = make_pair(u, i);
                q.push(make_pair(vd, v));
            }
        }
    }
    int cur = g;
    while (cur != s) {
        camps.push_back(cur);
        int u = bk[cur].first;
        edges[u][bk[cur].second].second *= 2;
        cur = u;
    }
    camps.push_back(s);
    return dist;
}

vector<int> dijkstra_2(int src) {
    vector<int> dist(n, inf);
    vector<bool> visit(n, false);
    pq q;
    dist[src] = 0;
    q.push(make_pair(0, src));
    while (!q.empty()) {
        int u = q.top().second; q.pop();
        if (visit[u]) continue;
        visit[u] = true;
        for (int i = 0; i < edges[u].size(); i++) {
            pi e = edges[u][i];
            int v = e.first;
            int cost = e.second;
            int vd = dist[u] + cost;
            if (vd < dist[v]) {
                dist[v] = vd;
                q.push(make_pair(vd, v));
            }
        }
    }
    return dist;
}

bool solve() {
    vector<int> dist = dijkstra_1();
    for (int i = 0; i < k; i++) {
        int base; cin >> base;
        --base;
        vector<int> b_dist = dijkstra_2(base);
        for (int camp: camps) {
            if (b_dist[camp] <= dist[camp]) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m >> k >> s >> g;
    --s; --g;
    for (int i = 0; i < m; i++) {
        int from, to, cost;
        cin >> from >> to >> cost;
        --from;
        --to;
        edges[from].push_back(make_pair(to, cost));
        edges[to].push_back(make_pair(from, cost));
    }
    cout << (solve() ? "We don't abandon team members" : "Gain Jui") << '\n';
}