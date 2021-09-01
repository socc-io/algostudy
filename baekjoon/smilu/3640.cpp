#include <bits/stdc++.h>
using namespace std;

#define INF 0x7FFFFFFF
#define NUM_NODE 202

struct Graph {
	struct Edge {
		int v, f, c, r; // destination, flow_capacity, cost, reverse_index;
    Edge(int v, int f, int c, int r): v(v), f(f), c(c), r(r) {}
  };
	int n;
	vector<vector<Edge>> edges;
	Graph(int n): n(n) {
		edges.resize(n);
	}
	void add_edge(int u, int v, int f, int c) {
		edges[u].emplace_back(v, f, c, edges[v].size());
		edges[v].emplace_back(u, 0, -c, edges[u].size() - 1);
	}
	vector<int> spfa(int src, int dst) {
		queue<int> q;
		vector<int> dist(n, INF);
		vector<int> back(n, -1);
		vector<bool> in_q(n, false);

		q.push(src);
		dist[src] = 0;
		in_q[src] = true;

		while(!q.empty()) {
			int u = q.front(); q.pop();
			in_q[u] = false;
			for (auto &e: edges[u]) {
				if (e.f <= 0) continue;
				int new_dist = dist[u] + e.c;
				if (dist[e.v] <= new_dist) continue;
				dist[e.v] = new_dist;
				back[e.v] = e.r;
				if (in_q[e.v]) continue;
				in_q[e.v] = true;
				q.push(e.v);
			}
		}

		vector<int> route;
		if (back[dst] == -1) return route;
		int cur = dst;
		while (back[cur] != -1) {
			Edge &vu = edges[cur][back[cur]];
			route.push_back(vu.r);
			cur = vu.v;
		}
		reverse(route.begin(), route.end());
		return route;
	}

	int min_flow(int src, vector<int> &route) {
		int cur = src;
		int mf = INF;
		for (int index: route) {
			Edge &e = edges[cur][index];
			mf = min(mf, e.f);
			cur = e.v;
		}
		return mf;
	}

	pair<int,int> apply_flow(int src, int f, vector<int> &route) {
		int cur = src;
		int sf = 0;
		int sc = 0;
		for (int index: route) {
			Edge &e = edges[cur][index];
			e.f -= f;
			edges[e.v][e.r].f += f;
			sf += f;
			sc += f * e.c;
			cur = e.v;
		}
		return make_pair(sf, sc);
	}

	pair<int,int> mcmf(int src, int dst) {
    // return: {max_flow, min_cost}
		pair<int,int> res;
		while (1) {
			vector<int> route = spfa(src, dst);
			if (route.size() == 0) break;
			int mf = min_flow(src, route);
			pair<int,int> sfc = apply_flow(src, mf, route);
			res.first += sfc.first;
			res.second += sfc.second;
		}
		return res;
	}
};

inline int outindex(int x) { return ((x << 1) | 1); }
inline int inindex(int x) { return (x << 1); }

bool solve() {
    int v, e;
    cin >> v >> e;

    if (cin.eof()) return false;

    Graph g((v<<1) + 2);
    g.add_edge(0, inindex(1), 2, 0);
    g.add_edge(outindex(v), 1, 2, 0);
    for (int i = 1; i <= v; i++) {
        const int f = 1 + (i == 1) + (i == v);
        g.add_edge(inindex(i), outindex(i), f, 0);
    }
    for (int i = 0; i < e; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        g.add_edge(outindex(a), inindex(b), 1, c);
    }
    const int min_cost = g.mcmf(0, 1).second;
    cout << min_cost << '\n';

    return true;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    while (solve());
}
