#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAX_N = 2000;
const int MAX_SEG = 8000;

inline ll relu(ll x) { return max(x, 0ll); }

struct Point {
  ll x, y;
  int type() const {
    return y > 0 || (y == 0 && x > 0);
  }
  ll cross(const Point &b) const {
    return x*b.y - y*b.x;
  }
  Point(ll x, ll y): x(x),y(y) {}
  Point() {}
  Point operator-(const Point &b) const {
    return Point(x - b.x, y - b.y);
  }
  bool operator<(const Point &b) const {
    if (type() != b.type()) return type() > b.type();
    return cross(b) > 0;
  }
};

struct MaxSubSumSeg {
  struct Node {
    ll sum, bst, pre, suf;
    Node (ll v) {
      sum = v;
      bst = relu(v);
      pre = relu(v);
      suf = relu(v);
    }
    Node() {
      sum = 0;
      bst = 0;
      pre = -0x3f3f3f3f3f3f3f3f;
      suf = -0x3f3f3f3f3f3f3f3f;
    }
    Node operator+(const Node &b) {
      Node ret;
      ret.sum = sum + b.sum;
      ret.bst = max(bst, b.bst);
      ret.bst = max(ret.bst, suf + b.pre);
      ret.pre = max(pre, sum + b.pre);
      ret.suf = max(b.suf, suf + b.sum);
      return ret;
    }
  };
  Node nodes[MAX_SEG];
  void update(int n, int s, int e, int x, ll v) {
    if (s == e) {
      nodes[n] = Node(v);
    } else {
      int m = (s+e)>>1, l = n<<1, r = l|1;
      if (x <= m) update(l,s,m,x,v);
      else update(r,m+1,e,x,v);
      nodes[n] = nodes[l] + nodes[r];
    }
  }
  Node query(int n, int s, int e, int f, int t) {
    if (t < s || e < f) return 0;
    if (f <= s && e <= t) return nodes[n];
    int m = (s+e)>>1, l = n<<1, r = l|1;
    auto L = query(l,s,m,f,t);
    auto R = query(r,m+1,e,f,t);
    return L + R;
  }
  // custom
  ll query() {
    return nodes[1].bst;
  }
  void update(int x, ll v) {
    update(1,0,MAX_N-1,x,v);
  }
} seg;

int n;
map<pair<int,int>,ll> cost;
Point pnt[2000];
ll wei[2000];
int ord[2000];
int pos[2000];

bool compare_pnt(int a, int b) {
  if (pnt[a].y != pnt[b].y) return pnt[a].y < pnt[b].y;
  return pnt[a].x > pnt[b].x;
}

int main(void)
{
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    ll x, y, v; scanf("%lld%lld%lld", &x, &y, &v);
    cost[{x, y}] += v;
  }
  n = cost.size();
  int piv = 0;
  for (auto it = cost.begin(); it != cost.end(); it++) {
    auto p = it->first;
    pnt[piv] = Point(p.first, p.second);
    wei[piv++] = it->second;
  }
  for (int i = 0; i < n; i++) ord[i] = i;
  sort(ord, ord+n, compare_pnt);
  for (int i = 0; i < n; i++) pos[ord[i]] = i;
  vector<pair<Point,pair<int,int>>> dir;
  for (int i = 0; i < n; i++) {
    for (int j = i+1; j < n; j++) {
      if (pos[i] > pos[j]) dir.push_back({pnt[i] - pnt[j], {i, j}});
      else dir.push_back({pnt[j] - pnt[i], {i, j}});
    }
  }
  sort(dir.begin(), dir.end());
  for (int i = 0; i < n; i++) {
    seg.update(pos[i], wei[i]);
  }
  ll ans = seg.query();
  Point lst; bool fnd = false;
  for (auto d: dir) {
    int i = d.second.first, j = d.second.second;	
    seg.update(pos[i], wei[j]);	
    seg.update(pos[j], wei[i]);	
    swap(pos[i], pos[j]);	
    if (fnd && lst < d.first) ans = max(ans, seg.query());	
    fnd = true;
    lst = d.first;
  }
  printf("%lld\n", ans);
}
