#include <cstdio>
#include <cstdlib>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

#define INF 0x3FFFFFFF

struct edge {
	int from;
	int to;
	int weight;
};

class graph
{
private:
	vector<edge*> _prev_of;
protected:
	vector< vector<edge*> > _edges_of;
	int _size;
public:
	graph(int size_) : _edges_of(size_), _size(size_), _prev_of(size_) {
		
	}
	~graph() {
		for(auto it = _edges_of.begin(); it != _edges_of.end(); ++it) {
			for(auto it2 = it->begin(); it2 != it->end(); ++it2) {
				delete (*it2);
			}
		}
	}
	void add_edge(int from_, int to_, int weight_) {
		edge* e = new edge{from_, to_, weight_};
		_edges_of[from_].push_back(e);
	}
	bool find_path_bfs(int src_, int sink_) {
		for(auto it = _prev_of.begin(); it != _prev_of.end(); ++it) (*it) = 0;
		queue<int> Q;
		Q.push(src_);
		while(!(Q.empty())) {
			int u = Q.front(); Q.pop();
			for(auto it = _edges_of[u].begin(); it != _edges_of[u].end(); ++it) {
				if((*it)->weight <= 0) continue;
				int v = (*it)->to;
				if(_prev_of[v] != 0 || v == src_) continue;
				_prev_of[v] = (*it);
				if(v == sink_) return true;
				Q.push(v);
			}
		}
		return false;
	}
	int backwarding(int sink_) {
		int cur = sink_;
		int min_weight = INF;
		while(_prev_of[cur] != 0) {
			edge* e = _prev_of[cur];
			if(min_weight > e->weight) min_weight = e->weight;
			cur = e->from;
		}
		cur = sink_;
		while(_prev_of[cur] != 0) {
			edge* e = _prev_of[cur];
			e->weight -= min_weight;
			bool already = false;
			for(auto it = _edges_of[e->to].begin(); it != _edges_of[e->to].end(); ++it) {
				if((*it)->to == e->from) {
					already = true;
					(*it)->weight += min_weight;
					break;
				}
			}
			if(!already) {
				edge* te = new edge{e->to, e->from, min_weight};
				_edges_of[e->to].push_back(te);
			}
			cur = e->from;
		}
		return min_weight;
	}
	int maximumFlow(int src_, int sink_) {
		int flow_sum = 0;
		while(find_path_bfs(src_, sink_)) {
			int flow = backwarding(sink_);
			flow_sum += flow;
		}
		return flow_sum;
	}
};

int main(int argc, char** argv)
{
	int n, m;
	scanf("%d%d", &n, &m);
	graph g(2 + n + m);
	for(int i=0;i<n;++i) {
		g.add_edge(0, 1+i, 1);
	}
	for(int i=0;i<n;++i) {
		int job_num;
		scanf("%d",&job_num);
		for(int j=0;j<job_num;++j) {
			int job_idx;
			scanf("%d", &job_idx); --job_idx;
			g.add_edge(1+i, 1+n+job_idx, 1);
		}
	}
	for(int i=0;i<m;++i) {
		g.add_edge(1+n+i,1+n+m,1);
	}
	int mf = g.maximumFlow(0, 1+n+m);
	printf("%d", mf);
	return 0;
}