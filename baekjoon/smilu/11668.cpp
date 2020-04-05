#include <cstdio>
#include <vector>
using namespace std;

#define NUM_WATER 1000
#define NUM_PIPE  1000

typedef pair<int,int> pii;
typedef long long lld;
typedef pair<lld, lld> pdd;

int ccw(pdd a, pdd b, pdd c) {
  lld op = a.first*b.second + b.first*c.second + c.first*a.second;
  op -= (a.second*b.first + b.second*c.first + c.second*a.first);
  if (op > 0) return 1;
  else if (op == 0) return 0;
  else return -1;
}

int is_intersect(pair<pdd, pdd> x, pair<pdd, pdd> y) {
  pdd a = x.first;
  pdd b = x.second;
  pdd c = y.first;
  pdd d = y.second;
  int ab = ccw(a, b, c)*ccw(a, b, d);
  int cd = ccw(c, d, a)*ccw(c, d, b);
  if (ab == 0 && cd == 0) {
    if (a > b) swap(a, b);
    if (c > d) swap(c, d);
    return c <= b && a <= d;
  }
  return ab <= 0 && cd <= 0;
}

int w, p; // the numbers of water sources, and pipes
pdd ws[NUM_WATER]; // positions of water sources
pair<pdd, pdd> ps[NUM_PIPE]; // pipes
vector<lld> cps[NUM_PIPE]; // collided pipes
int state[NUM_PIPE];

bool dfs(int u, int s) {
  if (state[u]) return true;
  state[u] = s;
  int ns = 3 - state[u];
  for (int v: cps[u]) {
    if (state[v] && state[v] != ns) return false;
    if (!dfs(v, ns)) return false;
  }
  return true;
}

int main(void)
{
  scanf("%d%d", &w, &p);
  for (int i = 0; i < w; i++) scanf("%lld%lld", &ws[i].first, &ws[i].second);
  for (int i = 0; i < p; i++) {
    int wi; // water source index
    scanf("%d%lld%lld", &wi, &ps[i].second.first, &ps[i].second.second); --wi;
    ps[i].first = ws[wi];
  }
  for (int i = 0; i < p; i++) {
    for (int j = i + 1; j < p; j++) {
      if (!is_intersect(ps[i], ps[j])) continue;
      if (ps[i].first == ps[j].first) continue;
      cps[i].push_back(j);
      cps[j].push_back(i);
    }
  }

  bool ans = true;
  for (int i = 0; i < p; i++) {
    if (!dfs(i, 1)) {
      ans = false;
      break;
    }
  }

  puts(ans ? "possible" : "impossible");

  return 0;
}
