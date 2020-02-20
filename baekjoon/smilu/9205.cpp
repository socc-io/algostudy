#include <cstdio>
#include <vector>
using namespace std;

typedef pair<int,int> pii;

int n;
pii ps[102];
vector<int> e[102];
bool r[102];

inline int abs(int a) { return a >= 0 ? a : -a; }

void reach(int u) {
  if (r[u]) return;
  r[u] = true;
  for (int i = 0; i < e[u].size(); i++) {
    reach(e[u][i]);
  }
}

void solve()
{
  scanf("%d", &n);
  n += 2;
  for (int i = 0; i < n; i++) {
    scanf("%d%d", &ps[i].first, &ps[i].second);
  }
  for (int i = 0; i < n; i++) {
    e[i].clear();
    r[i] = false;
  }
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      int d = abs(ps[i].first - ps[j].first) + abs(ps[i].second - ps[j].second);
      if (d <= 1000) {
        e[i].push_back(j);
        e[j].push_back(i);
      }
    }
  }
  reach(0);
  puts(r[n-1] ? "happy" : "sad");
}

int main(void)
{
  int t; scanf("%d", &t);
  while(t--) solve();
}