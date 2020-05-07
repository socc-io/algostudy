#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;

#define MAX_N 2100000

struct BIT {
  ll ft[MAX_N];
  void clear() { for (int i = 0; i < MAX_N; i++) ft[i] = 0; }
  void update(int x, ll v) {
    for (int i = x; i <= MAX_N; i+=(i&-i)) ft[i] += v;
  }
  void update(int a, int b, ll v) {
    update(a, v);
    update(b+1, -v);
  }
  ll query(int x) {
    ll ret = 0;
    for (int i = x; i > 0; i-=(i&-i)) ret += ft[i];
    return ret;
  }
} bit;

struct Query {
  int s, e;
  ll x;
} qs[300030];

int n, m, q;
vector<int> as[300030]; // own areas
ll ps[300030]; // the target number of asteroid
int ls[300030], rs[300030];
vector<int> ms[300030];

bool check(int ni) {
  ll sum = 0;
  for (int mi: as[ni]) {
    sum += bit.query(mi);
    if (sum >= ps[ni]) return true;
  }
return false;
}

int main(void)
{
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= m; i++) {
    int tmp; scanf("%d", &tmp);
    as[tmp].push_back(i);
  }
  for (int i = 1; i <= n; i++) scanf("%lld", &ps[i]);
  scanf("%d", &q);
  for (int i = 1; i <= q; i++) {
    scanf("%d%d%lld", &qs[i].s, &qs[i].e, &qs[i].x);
  }

  for (int i = 1; i <= n; i++) {
    ls[i] = 1;
    rs[i] = q+1;
  }

  while (1) {
    bool flag = false;
    for (int i = 1; i <= q; i++) ms[i].clear();
    for (int i = 1; i <= n; i++) {
      if (ls[i] == rs[i]) continue;
      ms[(ls[i]+rs[i])>>1].push_back(i);
      flag = true;
    }
    if (!flag) break;
    bit.clear();
    for (int i = 1; i <= q; i++) {
      int s = qs[i].s, e = qs[i].e;
      ll x = qs[i].x;
      if (s <= e) bit.update(s, e, x);
      else {
        bit.update(s, m, x);
        bit.update(1, e, x);
      }
      for (int j: ms[i]) {
        if (check(j)) {
          rs[j] = i;
        } else {
          ls[j] = i+1;
        }
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    if (ls[i] < q+1) printf("%d\n", ls[i]);
    else puts("NIE");
  }
}
