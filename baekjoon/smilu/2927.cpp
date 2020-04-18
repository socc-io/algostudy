#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

#define MAX_N 30001
#define MAX_Q 300000
#define MAX_R 20
#define MAX_V (4*MAX_N)

// struct Seg{
// 	int tree[1 << 18];
// 	int bias = 1 << 17;

// 	void update(int x, int v){
// 		x |= bias; tree[x] = v;
// 		while(x >>= 1){
// 			tree[x] = tree[x << 1] + tree[x << 1 | 1];
// 		}
// 	}

// 	int query(int l, int r){
// 		l |= bias, r |= bias;
// 		int ret = 0;
// 		while(l <= r){
// 			if(l & 1) ret += tree[l++];
// 			if(~r & 1) ret += tree[r--];
// 			l >>= 1, r >>= 1;
// 		}
// 		return ret;
// 	}
// };

struct Seg {
  int v[MAX_V];
  void _update(int node, int begin, int end, int index, int value) {
    if (index < begin || index >= end) return;
    if (begin + 1 == end) {
      v[node] = value;
      return;
    }
    int mid = (begin + end) >> 1;
    _update(node<<1, begin, mid, index, value);
    _update((node<<1)+1, mid, end, index, value);
    v[node] = v[node<<1] + v[(node<<1)+1];
  }
  int _query(int node, int begin, int end, int from, int to) {
    if (end <= from || begin >= to) return 0;
    if (from <= begin && end <= to) return v[node];
    int mid = (begin + end) >> 1;
    return _query(node<<1, begin, mid, from, to) +
           _query((node<<1)+1, mid, end, from, to);
  }
  void update(int index, int value) {
    _update(1, 0, MAX_N, index, value);
  }
  int query(int from, int to) {
    return _query(1, 0, MAX_N, from, to + 1);
  }
};

struct UnionFind {
  int p[MAX_N];
  void clear() {
    for (int i = 0; i < MAX_N; i++) p[i] = i;
  }
  int top(int a) {
    return (p[a] == a) ? a : (a = top(p[a]));
  }
  bool merge(int a, int b) {
    int ta = top(a), tb = top(b);
    if (ta == tb) return false;
    p[ta] = tb;
    return true;
  }
  bool like(int a, int b) {
    return top(a) == top(b);
  }
  UnionFind() { clear(); }
};

struct Query {
#define CMD_BRIDGE 0
#define CMD_PENGUINS 1
#define CMD_EXCURSION 2
  int cmd, a, b;
  void input() {
    char s[30];
    scanf("%s%d%d", s, &a, &b);
    if (s[0] == 'b') { // bridge
      cmd = CMD_BRIDGE;
    } else if (s[0] == 'p') { // penguins
      cmd = CMD_PENGUINS;
    } else { // excursion
      cmd = CMD_EXCURSION;
    }
  }
};

int n, qn;
int ci[MAX_N], m_ci; // chain index
int ct[MAX_N]; // chain top
int num[MAX_N], m_num; // hld node number
int pc[MAX_N]; // the number of penguins
int par[MAX_N][MAX_R]; // parents
int level[MAX_N];
int wei[MAX_N]; // weight
int hp[MAX_N]; // heavy index
vector<int> adj[MAX_N]; // adjacent nodes
Query queries[MAX_Q];
UnionFind uf;
Seg seg;

void build_tree(int u, int p) {
  level[u] = level[p] + 1;
  par[u][0] = p;
  for (int i = 1; i < MAX_R; i++) {
    par[u][i] = par[par[u][i-1]][i-1];
  }
  wei[u] = 1;
  hp[u] = 0;
  for (int v: adj[u]) {
    if (v == p) continue;
    build_tree(v, u);
    wei[u] += wei[v];
    if (hp[u] == 0 || wei[v] > wei[hp[u]]) {
      hp[u] = v;
    }
  }
}

void hl_decompose(int u, int p) {
  seg.update(m_num, pc[u]);
  num[u] = m_num++;
  ci[u] = m_ci;
  if (ct[m_ci] == 0) {
    ct[m_ci] = u;
  }
  if (hp[u]) hl_decompose(hp[u], u);
  for (int v: adj[u]) {
    if (v == p || v == hp[u]) continue;
    ++m_ci;
    hl_decompose(v, u);
  }
}

int query(int a, int b){
  if (!uf.like(a, b)) return -1;
	int ret = 0;
	while (ci[a] != ci[b]){
		if(level[ct[ci[a]]] < level[ct[ci[b]]]) swap(a, b);
    int st = ct[ci[a]];
		ret += seg.query(num[st], num[a]);
		a = par[st][0];
	}
	if(level[a] > level[b]) swap(a, b);
	ret += seg.query(num[a], num[b]);
	return ret;
}

int main(void)
{
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) scanf("%d", &pc[i]);
  scanf("%d", &qn);
  for (int i = 0; i < qn; i++) queries[i].input();

  for (int i = 0; i < qn; i++) {
    Query &q = queries[i];
    if (q.cmd != CMD_BRIDGE) continue;
    int a = q.a, b = q.b;
    if (uf.merge(a, b)) {
      adj[a].push_back(b);
      adj[b].push_back(a);
    }
  }
  for (int i = 2; i <= n; i++) {
    if (uf.merge(1, i)) {
      adj[1].push_back(i);
      adj[i].push_back(1);
    }
  }
  build_tree(1, 0);
  hl_decompose(1, 0);
  uf.clear();
  for (int i = 0; i < qn; i++) {
    Query &q = queries[i];
    if (q.cmd == CMD_BRIDGE) {
      puts(uf.merge(q.a, q.b) ? "yes" : "no");
    } else if (q.cmd == CMD_PENGUINS) {
      seg.update(num[q.a], q.b);
    } else { // excursion
      int res = query(q.a, q.b);
      if (res == -1) puts("impossible");
      else printf("%d\n", res);
    }
  }
}
