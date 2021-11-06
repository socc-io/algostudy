#include <bits/stdc++.h>
using namespace std;

const int MAXN = 30000;
const int MAXQ = 300000;

struct UnionFind {
	int par[MAXN + 1];
	UnionFind() {
		for (int i = 0; i <= MAXN; i++)
			par[i] = i;
	}
	int rt(int x) {
		return par[x] == x ? x : (par[x] = rt(par[x]));
	}
	bool same(int a, int b) { return rt(a) == rt(b); }
	bool merge(int a, int b) {
		a = rt(a);
		b = rt(b);
		if (a == b) return false;
		par[b] = a;
		return true;
	}
} uf, uf2;

struct Seg {
	static const int bias = 1<<15;
	int s[bias<<1];
	void rawset(int i, int v) { s[bias|i] = v; }
	void organize() {
		for (int i = bias-1; i > 0; i--)
			s[i] = s[i<<1] + s[(i<<1)|1];
	}
	void update(int i, int v) {
		i |= bias;
		int diff = v - s[i];
		do { s[i] += diff; } while (i >>= 1);
	}
	int query(int f, int t) {
		f |= bias; t |= bias;
		int res = 0;
		while (f <= t) {
			if ( f & 1) res += s[f++];
			if (~t & 1) res += s[t--];
			f >>= 1; t >>= 1;
		}
		return res;
	}
} seg;

struct Query {
	enum Operation: int {
		BRIDGE = 0,
		PENGUINS,
		EXCURSION
	};
	Operation op;
	int v1;
	int v2;
	void input() {
		string buf;
		cin >> buf >> v1 >> v2;
		if (buf[0] == 'b') op = BRIDGE;
		else if (buf[0] == 'p') op = PENGUINS;
		else op = EXCURSION;
	}
} qrs[MAXQ];

int n, q;
vector<int> adj[MAXN+1];
int iv[MAXN+1];
int top[MAXN+1];
int par[MAXN+1];
int depth[MAXN+1];
int sz[MAXN+1];
int in[MAXN+1];

void init_size(int u, int p) {
	sz[u] = 1;
	depth[u] = depth[p] + 1;
	par[u] = p;
	for (int &v: adj[u]) if (v != p) {
		init_size(v, u);
		sz[u] += sz[v];
		if (sz[v] > sz[adj[u][0]])
			swap(v, adj[u][0]);
	}
}

void init_hld(int u, int p) {
	int inc = in[u] + 1;
	for (int v: adj[u]) if (v != p) {
		in[v] = inc;
		inc += sz[v];
		top[v] = v == adj[u][0] ? top[u] : v;
		init_hld(v, u);
	}
}

int query(int a, int b) {
	int res = 0;
	while (top[a] != top[b]) {
		if (depth[top[a]] < depth[top[b]]) swap(a, b);
		res += seg.query(in[top[a]], in[a]);
		a = par[top[a]];
	}
	if (depth[a] > depth[b]) swap(a, b);
	res += seg.query(in[a], in[b]);
	return res;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> iv[i];
	cin >> q;
	for (int i = 0; i < q; i++) {
		qrs[i].input();
		if (qrs[i].op == Query::Operation::BRIDGE) {
			int v1 = qrs[i].v1, v2 = qrs[i].v2;
			if (!uf2.same(v1, v2)) {	
				adj[v1].push_back(v2);
				adj[v2].push_back(v1);
				uf2.merge(v1, v2);
			}
		}
	}
	for (int i = 2; i <= n; i++) {
		if (!uf2.same(1, i)) {
			adj[1].emplace_back(i);
			adj[i].emplace_back(1);
			uf2.merge(1, i);
		}
	}
	init_size(1, 0);
	init_hld(1, 0);
	for (int i = 1; i <= n; i++) seg.rawset(in[i], iv[i]);
	seg.organize();
	
	for (int i = 0; i < q; i++) {
		Query::Operation op = qrs[i].op;
		int v1 = qrs[i].v1, v2 = qrs[i].v2;
		if (op == Query::Operation::BRIDGE) {
			puts(uf.merge(v1, v2) ? "yes" : "no");
		} else if (op == Query::Operation::PENGUINS) {
			seg.update(in[v1], v2);
		} else { // EXCURSION
			if (uf.same(v1, v2))
				printf("%d\n", query(v1, v2));
			else
				puts("impossible");
		}
	}
	return 0;
}
