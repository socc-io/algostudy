#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

#define INF 0x7FFFFFF0
#define LL_INF 0x7FFFFFFFFFFFFFF0

typedef long long lld;

struct MCMF {
	int n;
	int capa[900][900];
	int cost[900][900];
	void add_edge(int from, int to, int _cost, int _capa) {
		capa[from][to] = _capa;
		cost[from][to] = _cost;
		cost[to][from] = -_cost;
	}
	pair<int,int> make_flow(int src, int dst) {
		vector<int> dist(n, INF);
		vector<int> bt(n, -1);
		vector<bool> inq(n, false);
		queue<int> q;

		q.push(src);
		inq[src] = true;
		bt[src] = src;
		dist[src] = 0;

		while (!q.empty()) {
			int u = q.front();
			q.pop();
			inq[u] = false;
			for (int v = 0; v < n; v++) {
				if (capa[u][v] <= 0) continue;
				int next_dist = dist[u] + cost[u][v];
				if (next_dist < dist[v]) {
					dist[v] = next_dist;
					bt[v] = u;
					if (!inq[v]) {
						q.push(v);
						inq[v] = true;
					}
				}
			}
		}

		if (bt[dst] == -1) return make_pair(0, 0);
		int cur = dst;
		int mf = INF;
		while(bt[cur] != cur) {
			int u = bt[cur];
			int v = cur;
			if (capa[u][v] < mf) mf = capa[u][v];
			cur = u;
		}
		cur = dst;
		int csum = 0;
		while(bt[cur] != cur) {
			int u = bt[cur];
			int v = cur;
			capa[u][v] -= mf;
			capa[v][u] += mf;
			csum += mf * cost[u][v];
			cur = u;
		}
		return make_pair(mf, csum);
	}
	pair<int,int> solve(int src, int dst) {
		pair<int,int> ans = {0, 0};
		while (1) {
			auto f = make_flow(src, dst);
			if (f.first == 0) break;
			ans.first += f.first;
			ans.second += f.second;
		}
		return ans;
	}
};

MCMF mcmf;

int main()
{
	int n, m;
	scanf("%d%d", &n, &m);
	mcmf.n = 2+n+m;
	for (int i = 0; i < n; i++) {
		int c, work, cost; scanf("%d", &c);
		for (int j = 0; j < c; j++) {
			scanf("%d%d", &work, &cost);
			mcmf.add_edge(2+i, 2+n+(work-1), cost, 1);
		}
	}
	for (int i = 0; i < n; i++) {
		mcmf.add_edge(0, 2+i, 0, 1);
	}
	for (int i = 0; i < m; i++) {
		mcmf.add_edge(2+n+i, 1, 0, 1);
	}
	auto ans = mcmf.solve(0, 1);
	printf("%d\n%d", ans.first, ans.second);
}
