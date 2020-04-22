#include <cstdio>
#include <algorithm>
using namespace std;

#define MAX_N 250000

int n, m;
int x[MAX_N];
int y[MAX_N];
int xi[MAX_N];
int yi[MAX_N];
int qu[MAX_N];
int qv[MAX_N];
int qx[MAX_N];
bool qa[MAX_N];
int qi[MAX_N];
int par[MAX_N];

struct Edge {
  int x, u, v;
  Edge() {}
  Edge(int x, int u, int v): x(x), u(u), v(v) {}
  bool operator<(const Edge &e) const { return x < e.x; }
} es[2*MAX_N];
int en, ek;

int getpar(int u) { return par[u] == u ? u : (par[u] = getpar(par[u])); }
bool merge(int a, int b) {
  int pa = getpar(a), pb = getpar(b);
  if (pa == pb) return false;
  par[pa] = pb;
  return true;
}

bool compare_x(int a, int b) { return x[a] < x[b]; }
bool compare_y(int a, int b) { return y[a] < y[b]; }
bool compare_qx(int a, int b) { return qx[a] < qx[b]; }

void advance(int th) {
  while (es[ek].x <= th && ek < en) {
    int u = es[ek].u, v = es[ek].v;
    merge(u, v);
    ek++;
  }
}
bool query(int u, int v) {
  return getpar(u) == getpar(v);
}

int main(void)
{
  scanf("%d%d", &n, &m);
  en = 2*(n-1);
  for (int i = 0; i < n; i++) {
    scanf("%d%d", &x[i], &y[i]);
    xi[i] = i;
    yi[i] = i;
    par[i] = i;
  }
  for (int i = 0; i < m; i++) {
    scanf("%d%d%d", &qu[i], &qv[i], &qx[i]);
    --qu[i], --qv[i];
    qi[i] = i;
  }
  sort(xi, xi+n, compare_x);
  sort(yi, yi+n, compare_y);
  sort(qi, qi+m, compare_qx);
  for (int i = 0; i < n-1; i++) {
    int u = xi[i], v = xi[i+1];
    es[i].x = abs(x[u]-x[v]);
    es[i].u = u;
    es[i].v = v;
  }
  for (int i = 0; i < n-1; i++) {
    int u = yi[i], v = yi[i+1];
    es[n-1+i].x = abs(y[u]-y[v]);
    es[n-1+i].u = u;
    es[n-1+i].v = v;
  }
  sort(es, es+en);
  for (int i = 0; i < m; i++) {
    int q = qi[i];
    advance(qx[q]);
    qa[q] = query(qu[q], qv[q]);
  }
  for (int i = 0; i < m; i++) {
    puts(qa[i] ? "YES" : "NO");
  }
}
