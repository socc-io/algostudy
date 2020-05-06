#include <cstdio>
#include <cassert>
#include <algorithm>
#include <queue>
#include <map>
#include <vector>
using namespace std;

typedef long long ll;
typedef pair<ll,int> pii;

int n, k;

struct Edge {
  bool dead;
  ll w;
  int l, r;
};

Edge ids[400400];
// multimap<int,int> ws;
priority_queue<pii> wq;
int idm;

int add_edge(ll w, int l, int r) {
  int id = idm++;
  ids[id] = {false,w,l,r};
  wq.push({w, id});
  return id;
}

ll pop_edges() {
  while (ids[wq.top().second].dead) wq.pop();
  int id = wq.top().second;
  Edge &e = ids[id];
  assert(e.l != -1);
  assert(e.r != -1);
  Edge &l = ids[e.l];
  Edge &r = ids[e.r];
  ll nw = l.w+r.w-e.w;
  l.dead = true;
  r.dead = true;
  e.dead = true;
  int nid = add_edge(nw, l.l, r.r);
  if (ids[nid].l >= 0) ids[ids[nid].l].r = nid;
  if (ids[nid].r >= 0) ids[ids[nid].r].l = nid;
  return e.w;
}

int main(void)
{
  scanf("%d", &n);
  k = (n+1)>>1;

  add_edge(-0x3f3f3f3f3f3f3f3f, -1, 1);
  for (int i = 1; i <= n; i++) {
    ll tmp; scanf("%lld", &tmp);
    add_edge(tmp, i-1, i+1);
  }
  add_edge(-0x3f3f3f3f3f3f3f3f, idm-1, -1);

  ll ans = 0;
  for (int i = 0; i < k; i++) {
    ans += pop_edges();
    printf("%lld\n", ans);
  }
}
