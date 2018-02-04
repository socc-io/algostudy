
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

struct position
{
	int x, y, z;
	void input() {
		scanf("%d%d%d", &x, &y, &z);
	}
};

struct edge {
	int a, b, w;
	bool operator<(const edge & b) const {
		return w < b.w;
	}
};

int n;
position pos[100000];
int group[100000];

int xs[100000];
int ys[100000];
int zs[100000];

edge edges[300000];
int edge_idx = 0;

int frt[100000];
int frt_idx = 0;

int find_root(int idx)
{
	frt_idx = 0;
	while(group[idx] != idx) {
		frt[frt_idx++] = idx;
		idx = group[idx];
	}
	for(int i=0; i<frt_idx; ++i) {
		group[frt[i]] = idx;
	}

	return idx;
}

int main(void)
{
	scanf("%d", &n); 
	for(int i=0; i<n; ++i) pos[i].input();
	
	for(int i=0; i<n; ++i) {
		xs[i] = i; 
		ys[i] = i;
		zs[i] = i;
	}
	
	sort(xs, xs+n, [](int a, int b) {
		return pos[a].x < pos[b].x;
	});
	sort(ys, ys+n, [](int a, int b) {
		return pos[a].y < pos[b].y;
	});
	sort(zs, zs+n, [](int a, int b) {
		return pos[a].z < pos[b].z;
	});

	for(int i=0; i<n-1; ++i) {
		int dx = pos[xs[i+1]].x - pos[xs[i]].x;
		int dy = pos[ys[i+1]].y - pos[ys[i]].y;
		int dz = pos[zs[i+1]].z - pos[zs[i]].z;
		edges[edge_idx++] = {xs[i], xs[i+1], dx};
		edges[edge_idx++] = {ys[i], ys[i+1], dy};
		edges[edge_idx++] = {zs[i], zs[i+1], dz};
	}

	sort(edges, edges + edge_idx);

	for(int i=0; i<n; ++i) group[i] = -1;

	int cost = 0;
	int edge_cnt = 0;

	for(int i=0; i<edge_idx; ++i) {
		edge e = edges[i];

		int a = e.a;
		int b = e.b;
		int w = e.w;

		if(group[a] == -1 && group[b] == -1) {
			group[b] = a;
			group[a] = a;
			cost += w;
			++edge_cnt;
		}
		else if(group[a] != -1 && group[b] == -1) {
			group[b] = find_root(a);
			cost += w;
			++edge_cnt;
		}
		else if(group[a] == -1 && group[b] != -1) {
			group[a] = find_root(b);
			cost += w;
			++edge_cnt;
		}
		else {
			int a_root = find_root(a);
			int b_root = find_root(b);
			if(a_root != b_root) {
				group[a_root] = b_root;
				cost += w;
				++edge_cnt;
			}
		}

		if(edge_cnt == n-1) break;
	}

	printf("%d\n", cost);

	return 0;
}