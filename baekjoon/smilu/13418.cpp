#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

struct edge
{
	int v1;
	int v2;
	int t;
};

int find_root(vector<int> &p, int idx)
{
	while(p[idx] != idx) {
		idx = p[idx];
	}
	return idx;
}

int main(void)
{
	int n, m;
	scanf("%d%d", &n,&m);
	++m;
	++n;
	vector<edge> edges;
	for(int i=0;i<m;++i) {
		int v1, v2, t;
		scanf("%d%d%d", &v1,&v2,&t);
		edges.push_back({v1,v2,1-t});
	}
	sort(edges.begin(), edges.end(), [](edge a, edge b) {
		return a.t < b.t;
	});
	vector<int> p(n);
	for(int i=0;i<n;++i) p[i] = i;
	int t_sum = 0;
	for(auto it = edges.begin(); it != edges.end(); ++it) {
		// printf("v1: %d, v2: %d, t: %d\n", it->v1, it->v2, it->t);
		int v1_root = find_root(p, it->v1);
		int v2_root = find_root(p, it->v2);
		if(v1_root == v2_root) continue;
		p[v1_root] = v2_root;
		t_sum += it->t;
	}
	// printf("end\n");
	int min_t = t_sum * t_sum;
	for(int i=0;i<n;++i) p[i] = i;
	t_sum = 0;
	for(auto it = edges.rbegin(); it != edges.rend(); ++it) {
		// printf("v1: %d, v2: %d, t: %d\n", it->v1, it->v2, it->t);
		int v1_root = find_root(p, it->v1);
		int v2_root = find_root(p, it->v2);
		if(v1_root == v2_root) continue;
		p[v1_root] = v2_root;
		t_sum += it->t;
	}
	int max_t = t_sum * t_sum;
	// printf("max: %d\n", max_t);
	// printf("min: %d\n", min_t);
	printf("%d", max_t - min_t);
}