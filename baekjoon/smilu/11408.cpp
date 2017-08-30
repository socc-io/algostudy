#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

#define INF 0x7FFFFFFF

struct Edge {
	int v, rev, w, cost;
	Edge(int v, int rev, int w, int cost): v(v), rev(rev), w(w), cost(cost) {}
};

int N, M;
int node_num;
int src, snk;
vector< vector<Edge> > edges;

vector<pair<int, int> > track;

bool spfa()
{
	queue<int> Q;
	vector<bool> in_Q(node_num, false);
	for(int i = 0; i < node_num; ++i) {
		track[i].first = -1;
		track[i].second = INF;
	}

	track[src].second = 0;
	in_Q[src] = true;
	Q.push(src);
	while(!Q.empty()) {
		int u = Q.front(); Q.pop();
		in_Q[u] = false;
		for(auto it = edges[u].begin(); it != edges[u].end(); ++it) {
			int v = it->v;
			int new_cost = track[u].second + it->cost;
			if(track[v].second > new_cost) {
				track[v].first = u;
				track[v].second = new_cost;
				if(!in_Q[v]) {
					Q.push(v);
					in_Q[v] = true;
				}
			}
		}
	}

	return (track[snk].first != -1);
}

int main(void)
{
	scanf("%d%d", &N, &M);
	node_num = N + M + 2;
	src = node_num - 2;
	snk = node_num - 1;
	nodes.resize(node_num);
	track.resize(node_num);
	for(int i = 0; i < N; ++i) {
		int job_size;
		scanf("%d", &job_size);
		for(int j = 0; j < job_size; ++j) {
			int job_num, cost;
			scanf("%d%d", &job_num, &cost);
			job_num = job_num - 1 + N;
			edges[i].push_back(Edge(job_num, edges[job_num].size(), 1, cost));
			edges[job_num].push_back(Edge(i, edges[i].size()-1, 0, -cost));
		}
		edges[src].push_back(Edge(i, edges[i].size(), 1, 0));
		edges[i].push_back(Edge(src, edges[src].size()-1, 0, 0));
	}
	for(int i = N; i < N + M; ++i) {
		edges[i].push_back(Edge(snk, edges[snk].size(), 1, 0));
		edges[snk].push_back(Edge(i, edge[i].size()-1, 0, 0));
	}

	while(spfa()) {
		for(int cur = snk; cur != src; cur = track[cur].first) {
			int u = track[cur].first;
			int v = cur;
		}
	}
}