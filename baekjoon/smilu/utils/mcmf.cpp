#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
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

// int n, m;
// int source, left, right, sink;
// Graph g(NUM_NODE);

// int main(void)
// {
// 	scanf("%d%d", &n, &m);
// 	source = 0;
// 	left = source + 1;
// 	right = left + n;
// 	sink = right + m;
// 	for (int i = 0; i < n; i++) {
// 		int t; scanf("%d", &t);
// 		g.add_edge(source, left + i, t, 0);
// 	}
// 	for (int i = 0; i < m; i++) {
// 		int t; scanf("%d", &t);
// 		g.add_edge(right + i, sink, t, 0);
// 	}
// 	for (int i = 0; i < m; i++) {
// 		for (int j = 0; j < n; j++) {
// 			int t; scanf("%d", &t);
// 			g.add_edge(left + j, right + i, INF, t);
// 		}
// 	}
// 	int mc = g.mcmf(source, sink).second;
// 	printf("%d\n", mc);
// }
