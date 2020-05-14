#include <bits/stdc++.h>
using namespace std;

struct col {
  int v[3];
  bool operator<(const col &y) const {
    if (v[0] != y.v[0]) return v[0] < y.v[0];
    if (v[1] != y.v[1]) return v[1] < y.v[1];
    return v[2] < y.v[2];
  }
} cs[200001];
int m, n;
int max_k;

struct point {
  int x, y;
  bool operator<(const point &p) const {
    if (x == p.x) return y < p.y;
    return x < p.x;
  }
} ps[200001];

set<point> ss[200001];
bool check_point(const point &p, int k) {
  const auto &s = ss[k];
  auto it = s.lower_bound(p);
  if (it == s.begin()) return false;
  --it;
  if (it->y < p.y) return true;
  return false;
}

void insert_point(const point &p, int k) {
  auto &s = ss[k];
  auto it = s.insert(p).first;
  ++it;
  while (it != s.end() && it->y >= p.y) {
    it = s.erase(it);
  }
}

void apply_point(const point &p) {
  int l = 1, r = max_k + 1;
  while (l < r) {
    int m = (l+r)/2;
    if (check_point(p, m)) l = m+1;
    else r = m;
  }
  max_k = max(max_k, l);
  insert_point(p, l);
}

int main(void)
{
  scanf("%d%d", &m, &n);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < n; j++) {
      if (m == 2 && i == 2) cs[j].v[2] = cs[j].v[1];
      else scanf("%d", &cs[j].v[i]);
    }
  }
  sort(cs, cs + n);
  for (int i = 0; i < n; i++) {
    ps[i].x = cs[i].v[1];
    ps[i].y = cs[i].v[2];
  }
  for (int i = 0; i < n; i++) apply_point(ps[i]);
  printf("%d\n", max_k);
}
