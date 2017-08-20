#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>

#define INF 0x7FFFFFFF

using namespace std;

int N;
char table[11][12];

const int price[4][4] = {
	100, 70, 40, 0,
	70 , 50, 30, 0,
	40 , 30, 20, 0,
	0  , 0 , 0 , 0
};
const int dir[4][2] = {1, 0, -1, 0, 0, 1, 0, -1};

struct MCMF
{
	struct Edge
	{
		int end, cap, cost, rev;
		Edge(int end, int cap, int cost, int rev): end(end), cap(cap), cost(cost), rev(rev) {}
	};
	int N;
	vector< vector<Edge> > edges;
	MCMF(int N) : N(N), edges(N) {}
	void push(int w, int v, int cap, int cost) {
		edges[w].push_back(Edge(v, cap, cost, edges[v].size()));
		edges[v].push_back(Edge(w, 0, -cost, edges[w].size() - 1));
	}
	int get_cost()
	{
		int cost = 0;

		while(true)
		{
			queue<int> Q;
			vector<int> D(N, INF);
			vector<int> T(N);
			vector<int> F(N);
			vector<int> I(N);
			vector<bool> Q_in(N, false);

			Q.push(0);
			D[0] = 0;
			Q_in[0] = true;

			while(!Q.empty()) {
				int u = Q.front(); Q.pop();
				Q_in[u] = false;
				for(auto eit = edges[u].begin(); eit != edges[u].end(); ++eit) {
					int v = eit->end;
					if(eit->cap > 0 && D[u] + eit->cost < D[v]) {
						D[v] = D[u] + eit->cost;
						T[v] = u;
						I[v] = distance(edges[u].begin(), eit);
						F[v] = eit->cap;
						if(!Q_in[v]) {
							Q.push(v);
							Q_in[v] = true;
						}
					}
				}
			}

			if(D[1] == INF) break;

			int min_flow = INF;
			for(int cur = 1; cur != 0; cur = T[cur]) {
				if(F[cur] < min_flow) min_flow = F[cur];
			}

			for(int cur = 1; cur != 0; cur = T[cur]) {
				int s = T[cur];
				edges[s][I[cur]].cap -= min_flow;
				edges[cur][edges[s][I[cur]].rev].cap += min_flow;
				cost += edges[s][I[cur]].cost * min_flow;
			}

			// printf("Cost: %d\n    ", cost);
			// for(int cur = T[1]; cur != 0; cur = T[cur]) {
			// 	printf("%d, ", cur - 2);
			// } printf("\n");
		}

		return -cost;
	}
};

int main(void)
{
	scanf("%d", &N);
	for(int i = 0; i < N; ++i) {
		scanf("%s", table[i]);
		for(int j = 0; j < N; ++j) {
			if(table[i][j] == 'F') table[i][j] = 3;
			else table[i][j] -= 'A';
		}
	}

	MCMF mcmf(N*N + 2);

	for(int i = 0; i < N; ++i) {
		for(int j = 0; j < N; ++j) {
			int idx = 2 + i * N + j;
			int grade = table[i][j];
			if((i + j) & 1) {
				mcmf.push(idx, 1, 1, 0);
			}
			else {
				for(int k = 0; k < 4; ++k) {
					int nx = i + dir[k][0], ny = j + dir[k][1];
					if(nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
					mcmf.push(idx, 2 + nx * N + ny, 1, -price[grade][table[nx][ny]]);
				}
				mcmf.push(0, idx, 1, 0);
				mcmf.push(idx, 1, 1, 0);
		 	}
		}
	}

	printf("%d", mcmf.get_cost());
}