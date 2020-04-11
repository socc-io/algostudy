#include <cstdio>
#include <set>
#include <algorithm>
using namespace std;

struct cake {
  double sz;
  int cnt;
  cake(int sz, int cnt = 1): sz(sz), cnt(cnt) {}
  bool operator<(const cake &c) const {
    return sz / cnt < c.sz / c.cnt;
  }
  cake next() const {
    return cake(sz, cnt+1);
  }
  double p() const {
    return sz / cnt;
  }
};

int n, m;
multiset<cake> cakes;

int main(void)
{
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    int sz; scanf("%d", &sz);
    cakes.insert(cake(sz));
  }
  scanf("%d", &m);
  double ans = 1e10;
  for (int i = 0; i < m; i++) {
    auto rbegin = cakes.end(); --rbegin;
    auto begin = cakes.begin();
    double diff = rbegin->p() - begin->p();
    ans = min(ans, diff);
    cakes.insert(rbegin->next());
    cakes.erase(rbegin);
  }
  auto rbegin = cakes.end(); --rbegin;
  ans = min(ans, rbegin->p() - cakes.begin()->p());
  printf("%.12f\n", ans);
}
