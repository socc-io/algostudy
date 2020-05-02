// https://csacademy.com/contest/round-70/task/and-or-max/solution/

#include <iostream>
#include <algorithm>
using namespace std;

struct Node {
  int as, os, mx, at, ot;
  Node(int v=0) {
    as = v;
    os = v;
    mx = v;
    at = (1<<20)-1;
    ot = 0;
  }
} tree[800001];

int a[200001];

void join(int n) {
  int l = n<<1, r = l|1;
  tree[n].as = tree[l].as & tree[r].as;
  tree[n].os = tree[l].os | tree[r].os;
  tree[n].mx = max(tree[l].mx, tree[r].mx);
}

void build_tree(int n, int s, int e) {
  if (s == e) {
    tree[n] = Node(a[s]);
  } else {
    int m = (s+e)>>1, l = n<<1, r = l|1;
    build_tree(l,s,m);
    build_tree(r,m+1,e);
    join(n);
  }
}

void push(int n, int s, int e) {
  tree[n].mx &= tree[n].at;
  tree[n].as &= tree[n].at;
  tree[n].os &= tree[n].at;
  tree[n].mx |= tree[n].ot;
  tree[n].as |= tree[n].ot;
  tree[n].os |= tree[n].ot;
  if (s != e) {
    int l = n<<1, r = l|1;
    tree[l].at &= tree[n].at;
    tree[l].ot &= tree[n].at;
    tree[r].at &= tree[n].at;
    tree[r].ot &= tree[n].at;

    tree[l].ot |= tree[n].ot;
    tree[r].ot |= tree[n].ot;
  }
  tree[n].at = (1<<20)-1;
  tree[n].ot = 0;
}

void update(int n, int s, int e, int f, int t, int val, int is_or) {
  push(n, s, e);
  if (t < s || e < f) return;
  if (f <= s && e <= t) {
    if (!((tree[n].os ^ tree[n].as) & (is_or ? val : ~val))) {
      if (is_or) {
        tree[n].ot |= val;
      } else {
        tree[n].at &= val;
        tree[n].ot &= val;
      }
      push(n, s, e);
      return;
    }
  }
  int m = (s+e)>>1, l = n<<1, r = l|1;
  update(l, s, m, f, t, val, is_or);
  update(r, m+1, e, f, t, val, is_or);
  join(n);
}

int query_max(int n, int s, int e, int f, int t) {
  push(n, s, e);
  if (t < s || e < f) return 0;
  if (f <= s && e <= t) return tree[n].mx;
  int m = (s+e)>>1, l = n<<1, r = l|1;
  int ans = max(
    query_max(l,s,m,f,t),
    query_max(r,m+1,e,f,t));
  join(n);
  return ans;
}

int main(void)
{
  int n, q;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
  build_tree(1, 1, n);
  scanf("%d", &q);
  while (q--) {
    int cmd, a, b, c;
    scanf("%d", &cmd);
    if (cmd == 1) {
      scanf("%d%d%d", &a, &b, &c);
      update(1, 1, n, a, b, c, 0);
    } else if (cmd == 2) {
      scanf("%d%d%d", &a, &b, &c);
      update(1, 1, n, a, b, c, 1);
    } else {
      scanf("%d%d", &a, &b);
      printf("%d\n", query_max(1, 1, n, a, b));
    }
  }
}