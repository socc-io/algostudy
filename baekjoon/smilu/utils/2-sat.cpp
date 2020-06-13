#include <cstdio>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

#define MAX 20000

typedef pair<int,int> pii;

int n, m, piv;

char pred[MAX];
vector<int> e[MAX];

int cnt, dfsn[MAX], SN, sn[MAX];
bool finished[MAX];
stack<int> S;
vector<vector<int>> scc;

int find_scc(int curr){
    dfsn[curr] = ++cnt;
    S.push(curr);
 
    int result = dfsn[curr];
    for(int next: e[curr]) {
        if(dfsn[next] == 0) result = min(result, find_scc(next));
        else if(!finished[next]) result = min(result, dfsn[next]);
    }
 
    if(result == dfsn[curr]){
        vector<int> curr_scc;
        while(1){
            int t = S.top();
            S.pop();
            curr_scc.push_back(t);
            finished[t] = true;
            sn[t] = SN;
            if(t == curr) break;
        }
        scc.push_back(curr_scc);
        SN++;
    }
    return result;
}

bool falsy(int index) { return index >= n; }

int get_index(int v) {
  if (v < 0) return piv + v + 1;
  return v - 1;
}
int rev_index(int v) {
  if (falsy(v)) return piv - v;
  return v;
}

int main(void)
{
  scanf("%d%d", &n, &m);
  piv = 2*n-1;
  for (int i = 0; i < m; i++) {
    int a, b; scanf("%d%d", &a, &b);
    a = get_index(a); b = get_index(b);
    e[piv - a].push_back(b);
    e[piv - b].push_back(a);
  }

  for(int i=0; i<2*n; i++)
    if(dfsn[i] == 0) find_scc(i);

  for (int i = 0; i < n; i++) {
    if (sn[i] == sn[piv - i]) {
      puts("0");
      return 0;
    }
  }

  puts("1");

  vector<pii> ps(n*2);
  for (int i = 0; i < n*2; i++) ps[i] = {sn[i], i};
  sort(ps.begin(), ps.end());
  
  for (int i=n*2-1; i >= 0; i--) {
    int u = ps[i].second;
    int ri = rev_index(u);
    if (pred[ri] == 0) pred[ri] = falsy(u) ? 1 : -1;
  }

  for (int i = 0; i < n; i++) printf("%d ", pred[i] > 0);
  puts("");
}

#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pi;

class SCC: public vector<vector<int>> {
  vector<int> dfsn;
  vector<bool> finished;
  vector<int> sn;
  stack<int> s;
  int piv;
public:
  int n;
  vector<vector<int>> adj;
  void add_edge(int u, int v) { adj[u].push_back(v); }
  int dfs(int u) {
    dfsn[u] = ++piv;
    s.push(u);

    int res = dfsn[u];
    for (int v: adj[u]) {
      if (dfsn[v] == 0) res = min(res, dfs(v));
      else if (!finished[v]) res = min(res, dfsn[v]);
    }

    if (res == dfsn[u]) {
      vector<int> vs;
      while (1) {
        int t = s.top(); s.pop();
        vs.push_back(t);
        finished[t] = true;
        sn[t] = size();
        if (t == u) break;
      }
      sort(vs.begin(), vs.end());
      push_back(vs);
    }

    return res;
  }
  void execute() {
    piv = 0;
    sn.resize(n, 0);
    dfsn.resize(n, 0);
    finished.resize(n, false);
    while (!s.empty()) s.pop();
    for (int i = 0; i < n; i++) {
      if (dfsn[i] == 0) dfs(i);
    }
  }
  int get(int x) const { return sn[x]; }
  SCC(int n): n(n), adj(n) {}
};

class TwoSAT {
  SCC scc;
  int _id(int x) {
    if (x < 0) return n2+x;
    return x-1;
  }
  int _not(int x) {
    return n2-1-x;
  }
public:
  const int n, n2;
  TwoSAT(int n): scc(n*2), n(n), n2(n*2) {}
  void add_edge(int u, int v) {
    u = _id(u); v = _id(v);
    int nu = _not(u), nv = _not(v);
    scc.add_edge(u, v);
    scc.add_edge(nv, nu);
  }
  vector<int> execute() {
    vector<int> pred;

    scc.execute();
    for (int i = 0; i < n; i++) {
      int j = _not(i);
      if (scc.get(i) == scc.get(j)) return pred;
    }

    vector<pi> ps(n2);
    for (int i = 0; i < n2; i++)
      ps[i] = {scc.get(i), i};
    sort(ps.begin(), ps.end());

    pred.resize(n);
    for (int i = n2-1; i >= 0; i--) {
      int u = ps[i].second;
      int v = (u >= n ? _not(u) : u);
      if (pred[v] == 0) pred[v] = (u>=n) ? 1 : -1;
    }

    return pred;
  }
};
