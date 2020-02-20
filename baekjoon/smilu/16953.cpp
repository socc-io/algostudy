#include <cstdio>
#include <queue>
#include <map>
using namespace std;

typedef unsigned long long llu;

llu a, b;

int main(void)
{
  scanf("%llu%llu", &a, &b);
  queue<llu> q;
  map<llu,int> cost;
  cost[a] = 1;
  q.push(a);
  while(!q.empty()) {
    llu u = q.front(); q.pop();
    llu vs[] = { u << 1, u * 10 + 1 };
    int nc = cost[u] + 1;
    for (int i = 0; i < 2; i++) {
      llu v = vs[i];
      if (v > b) continue;
      else if (v == b) {
        printf("%d", nc);
        return 0;
      }
      cost[v] = nc;
      q.push(v);
    }
  }
  puts("-1");
}