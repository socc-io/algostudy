#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAX_SEG = 1<<19;

inline ll relu(ll x) { return max(x, 0ll); }

ll n, m, k, d;

struct MaxSubSumSeg {
  struct Node {
    ll sum, bst, pre, suf;
    Node (ll v) {
      sum = v;
      bst = relu(v);
      pre = relu(v);
      suf = relu(v);
    }
    Node() {}
    Node operator+(const Node &b) {
      Node ret;
      ret.sum = sum + b.sum;
      ret.bst = max(bst, b.bst);
      ret.bst = max(ret.bst, suf + b.pre);
      ret.pre = max(pre, sum + b.pre);
      ret.suf = max(b.suf, suf + b.sum);
      return ret;
    }
    void operator+=(const ll v) {
      sum += v;
      bst = relu(sum);
      pre = relu(sum);
      suf = relu(sum);
    }
  };
  Node nodes[MAX_SEG];
  void update(int n, int s, int e, int x, ll v) {
    if (s == e) {
      nodes[n] += v;
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
  void update(int x, ll v) {
    update(1, 1, n, x, v);
  }
  ll query(int f, int t) {
    return query(1, 1, n, f, t).bst;
  }
} seg;

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cin >> n >> m >> k >> d;
  ll dk = d * k;
  for (int i = 1; i <= n; i++) seg.update(i, -k);
  while (m--) {
    int num, sz; cin >> sz >> num;
    seg.update(sz, num);
    if (seg.query(1, n) > dk) puts("NIE");
    else puts("TAK");
  }
}
