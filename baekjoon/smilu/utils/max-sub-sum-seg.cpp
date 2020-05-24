#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAX_N = 2000;
const int MAX_SEG = 8000;

inline ll relu(ll x) { return max(x, 0ll); }

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
} seg;
