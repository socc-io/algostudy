#include <cstdio>
#include <vector>
using namespace std;

struct Seg {
  int xv[400000];
  void update(int n, int s, int e, int idx, int val) {
    if (idx < s || idx > e) return;
    if (s == e) {
      xv[n] = val;
      return;
    }
    int m = (s+e)>>1, l = n<<1, r = l|1;
    update(l,s,m,idx,val);
    update(r,m+1,e,idx,val);
    xv[n] = xv[l] ^ xv[r];
  }
  int query(int n, int s, int e, int f, int t) {
    if (t < s || e < f) return 0;
    if (f <= s && e <= t) return xv[n];
    int m = (s+e)>>1, l = n<<1, r = l|1;
    return query(l,s,m,f,t) ^ query(r,m+1,e,f,t);
  }
} seg;

int n, q;
vector<int> adj[100001];
int arr[100001];
int par[100001];
int lev[100001];
int sz[100001];
int nn[100001], nni = 1;
int top[100001];

void build_tree(int u, int p) {
  par[u] = p;
  lev[u] = lev[p]+1;
  sz[u] = 1;
  for (int &v: adj[u]) {
    if (v == p) continue;
    build_tree(v, u);
    sz[u] += sz[v];
    if (sz[v] > sz[adj[u][0]]) {
      swap(v, adj[u][0]);
    }
  }
}

void build_hld(int u, int p, int pt) {
  nn[u] = nni++;
  top[u] = pt;
  bool hv = true;
  for (int v: adj[u]) {
    if (v == p) continue;
    build_hld(v, u, hv ? pt : v);
    hv = false;
  }
}

int query(int a, int b) {
  int ret = 0;
  while (top[a] != top[b]) {
    if (lev[top[a]] < lev[top[b]]) swap(a, b);
    ret ^= seg.query(1,1,n,nn[top[a]],nn[a]);
    a = par[top[a]];
  }
  if (lev[a] < lev[b]) swap(a, b);
  ret ^= seg.query(1,1,n,nn[b],nn[a]);
  return ret;
}

void update(int a, int b) {
  seg.update(1,1,n,nn[a],b);
}

int main(void)
{
  scanf("%d%d", &n, &q);
  for (int i = 1; i <= n; i++) scanf("%d", &arr[i]);
  for (int i = 1; i < n; i++) {
    int x, y; scanf("%d%d", &x, &y);
    adj[x].push_back(y);
    adj[y].push_back(x);
  }
  build_tree(1, 0);
  build_hld(1, 0, 1);
  for (int i = 1; i <= n; i++) update(i, arr[i]);
  while (q--) {
    int cmd, a, b;
    scanf("%d%d%d", &cmd, &a, &b);
    if (cmd == 2) {
      printf("%d\n", query(a, b));
    } else {
      update(a, b);
    }
  }
}
