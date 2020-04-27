#include <cstdio>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

typedef long long lld;

struct Point {
  int x, y;
  Point operator-(const Point &p) const {
    return {x-p.x, y-p.y};
  }
  void input() { scanf("%d%d", &x, &y); }
};

int ccw(Point a, Point b) {
  int res = a.x*b.y-a.y*b.x;
  if (res > 0) return 1;
  if (res == 0) return 0;
  return -1;
}

struct Bar {
  Point a, b;
  void input() { a.input(); b.input(); }
  bool collide(const Bar &o) const {
    if (ccw(b-a, o.a-a)*ccw(b-a, o.b-a) >= 0) return false;
    return ccw(o.b-o.a, a-o.a)*ccw(o.b-o.a, b-o.a) < 0;
  }
} bars[3000];

int n, bn;

struct SCC {
  vector<int> adj[6000];
  int num[6000];
  int sn[6000];
  int num_k, sn_k;
  bool finished[6000];
  stack<int> s;
  vector<vector<int>> items;

  int build(int cur) {
    num[cur] = ++num_k;
    s.push(cur);

    int res = num[cur];
    for (int nxt: adj[cur]) {
      if (num[nxt] == 0) res = min(res, build(nxt));
      else if (!finished[nxt]) res = min(res, num[nxt]);
    }

    if (res == num[cur]) {
      vector<int> v;
      while (1) {
        int t = s.top(); s.pop();
        v.emplace_back(t);
        finished[t] = true;
        sn[t] = sn_k;
        if (t == cur) break;
      }
      sort(v.begin(), v.end());
      items.push_back(v);
      ++sn_k;
    }

    return res;
  }

  void insert(int from, int to) {
    adj[from].emplace_back(to);
  }

  void run(int n) {
    for (int i = 0; i < n; i++) if(num[i] == 0) {
      build(i);
    }
    sort(items.begin(), items.end());
  }
};

struct SAT {
  SCC scc;
  void insert(int from, int to) { scc.insert(from, to); }
  bool valid(int n) {
    for (int i = 0; i < n; i++) {
      if (scc.sn[i<<1] == scc.sn[(i<<1)|1]) {
        return false;
      }
    }
    return true;
  }
  vector<int> run(int n) {
    int m = n<<1;
    scc.run(m);
    if (!valid(n)) return vector<int>();
    vector<int> res(n, -1);
    vector<pair<int,int>> p(m);
    for (int i = 0; i < m; i++) {
      p[i] = {scc.sn[i], i};
    }
    sort(p.begin(), p.end());
    for (int i = m-1; i >= 0; i--) {
      int var = p[i].second;
      if (res[var>>1] == -1) res[var>>1] = (var&1);
    }
    return res;
  }
} sat;

int main(void)
{
  scanf("%d", &n); bn = 3*n;
  for (int i = 0; i < bn; i++) bars[i].input();
  for (int i = 0; i < n; i++) {
    int a = i*3, b = i*3+1, c = i*3+2;
    sat.insert((a<<1)|1, b<<1);
    sat.insert((a<<1)|1, c<<1);
    sat.insert((b<<1)|1, a<<1);
    sat.insert((b<<1)|1, c<<1);
    sat.insert((c<<1)|1, a<<1);
    sat.insert((c<<1)|1, b<<1);
  }
  for (int i = 0; i < bn; i++) {
    for (int j = i+1; j < bn; j++) {
      if (bars[i].collide(bars[j])) {
        sat.insert(i<<1, (j<<1)|1);
        sat.insert(j<<1, (i<<1)|1);
      }
    }
  }
  vector<int> res = sat.run(bn);
  if (res.size() == 0) {
    puts("-1");
    return 0;
  }
  vector<int> ans;
  for (int i = 0; i < bn; i++) {
    if (!res[i]) ans.push_back(i);
  }
  printf("%lu\n", ans.size());
  for (int v: ans) printf("%d ", v+1); puts("");
}
