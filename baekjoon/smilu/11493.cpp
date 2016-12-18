#include <cstdio>
#include <vector>
#include <deque>
using namespace std;
#define INF 0x3FFFFFFF

struct edge
{
	int from;
	int to;
	int cap;
	int cost;
};

int map[500][500];
bool floor[500];
bool coin[500];
int wb[500];
int wb_idx;
int bw[500];
int bw_idx;
int mat[250][250];
int n, m;
int mat_size;
int graph_size;

edge* make_edge(int from, int to, int cap, int cost)
{
	edge* e = new edge{from, to, cap, cost};
	return e;
}

int rebuild(vector< vector<edge*> > &graph, vector<edge*> &track)
{
	int size = graph.size();
	int cur = size - 1;
	int min_cap = INF;
	while(cur != 0) {
		edge* e = track[cur];
		if(e->cap < min_cap) {
			min_cap = e->cap;
		}
		cur = e->from;
	}
	cur = size - 1;
	while(cur != 0) {
		edge* e = track[cur];
		e->cap -= min_cap;
		cur = e->from;
	}
	cur = size - 1;
	int cost_sum = 0;
	while(cur != 0) {
		edge* e = track[cur];
		cost_sum += e->cost;
		int u = e->to;
		int v = e->from;
		bool already = false;
		for(auto it = graph[u].begin(); it != graph[u].end(); ++it) {
			if((*it)->to == v) {
				already = true;
				(*it)->cap += min_cap;
				break;
			}
		}
		if(!already) {
			graph[u].push_back(make_edge(u,v,min_cap,(-1)*(e->cost)));
		}
		cur = e->from;
	}
	return min_cap * cost_sum;
}

bool spfa(vector< vector<edge*> > &graph, vector<edge*> &track)
{
	int size = graph.size();
	deque<int> Q;
	vector<int> k(size, INF);
	k[0] = 0;
	Q.push_back(0);
	while(!(Q.empty()))
	{
		int u = Q.front(); Q.pop_front();
		for(auto it = graph[u].begin(); it != graph[u].end(); ++it) {
			if((*it)->cap <= 0) continue;
			int v = (*it)->to;
			int new_k = k[u] + (*it)->cost;
			if(new_k < k[v]) {
				k[v] = new_k;
				track[v] = (*it);
				bool already = false;
				for(auto it2 = Q.begin(); it2 != Q.end(); ++it2) {
					if((*it2) == v) {
						already = true;
						break;
					}
				}
				if(!already) {
					Q.push_back(v);
				}
			}
		}
	}
	return k[size-1] != INF;
}

int mcmf(vector< vector<edge*> > &graph)
{
	int size = graph.size();
	vector<edge*> track(size);
	int cs = 0;
	while(spfa(graph, track)) {
		cs += rebuild(graph, track);
	}
	return cs;
}

int get_min_cost()
{
	graph_size = (mat_size<<1) + 2;
	vector< vector<edge*> > graph(graph_size);
	for(int i=0;i<mat_size;++i) {
		graph[0].push_back(make_edge(0,1+i,1,0));
	}
	for(int i=0;i<mat_size;++i) {
		for(int j=0;j<mat_size;++j) {
			if(mat[i][j] || 1) {
				graph[1+i].push_back(make_edge(1+i,1+mat_size+j,1,mat[i][j]));
			}
		}
	}
	for(int i=0;i<mat_size;++i) {
		graph[1+mat_size+i].push_back(make_edge(1+mat_size+i,graph_size-1,1,0));
	}
	return mcmf(graph);
}

void map_floyd()
{
	for(int k=0;k<n;++k) {
		for(int i=0;i<n;++i) {
			for(int j=0;j<n;++j) {
				int new_weight = map[i][k] + map[k][j];
				if(new_weight < map[i][j]) {
					map[i][j] = new_weight;
				}
			}
		}
	}
}

void RUN()
{
	scanf("%d%d", &n,&m);
	for(int i=0;i<n;++i) for(int j=0;j<n;++j) map[i][j] = INF;
	for(int i=0;i<m;++i) {
		int a, b;
		scanf("%d%d", &a,&b); --a; --b;
		map[a][b] = 1;
		map[b][a] = 1;
	}
	map_floyd();
	for(int i=0;i<n;++i) {
		int val; scanf("%d", &val);
		floor[i] = (val&1);
	}
	for(int i=0;i<n;++i) {
		int val; scanf("%d", &val);
		coin[i] = (val&1);
	}
	wb_idx = 0; bw_idx = 0;
	for(int i=0;i<n;++i) {
		     if(!floor[i] &&  coin[i]) bw[bw_idx++] = i;
		else if( floor[i] && !coin[i]) wb[wb_idx++] = i;
	}
	mat_size = wb_idx;
	for(int i=0;i<mat_size;++i) {
		int wb_val = wb[i];
		for(int j=0;j<mat_size;++j) {
			int bw_val = bw[j];
			mat[i][j] = map[wb_val][bw_val];
		}
	}
	int pre_value = 0;
	int min_value;
	for(int i=0;i<mat_size;++i) {
		min_value = INF;
		for(int j=0;j<mat_size;++j) {
			if(mat[i][j] < min_value) {
				min_value = mat[i][j];
			}
		}
		for(int j=0;j<mat_size;++j) {
			mat[i][j] -= min_value;
		}
		pre_value += min_value;
	}
	for(int i=0;i<mat_size;++i) {
		min_value = INF;
		for(int j=0;j<mat_size;++j) {
			if(mat[j][i] < min_value) {
				min_value = mat[j][i];
			}
		}
		for(int j=0;j<mat_size;++j) {
			mat[j][i] -= min_value;
		}
		pre_value += min_value;
	}
	int min_cost = get_min_cost();
	printf("%d\n", min_cost + pre_value);
}

int main(void)
{
	int T;
	scanf("%d", &T);
	for(int test_idx=0; test_idx<T; ++test_idx) {
		RUN();
	}
}
