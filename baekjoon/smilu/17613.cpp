#include <cstdio>
#include <algorithm>
#include <map>
using namespace std;

map<pair<int,int>, int> cache;
int query(int s, int e, int is) {
  if (s == e) {
    if (s == 0) return 0;
    if (s == 1) return 1;
  }

  auto it = cache.find({s, e});
  if (it != cache.end()) {
    return it->second;
  }

  // printf("s: %d, e: %d\n", s, e);
  int ret = 0;
  for (int i = is; i >= 1; i--) {
    int l = (1<<i)-1;
    int r = (1<<(i+1))-2;
    if (l > e) continue;
    if (r < s) break;
    int ns = max(s, l), ne = min(e, r);
    ret = max(ret, query(ns-l, ne-l, i)+i);
  }

  cache[{s, e}] = ret;
  return ret;
}

int main(void)
{
  int t; scanf("%d", &t);
  while (t--) {
    int a, b; scanf("%d%d", &a, &b);
    printf("%d\n", query(a, b, 30));
  }
}
