#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 50050;

int n, m;
int par[MAX_N];
vector<int> adj[MAX_N];
int nin[MAX_N];
int ord[MAX_N];

int root(int x) { return x == par[x] ? x : (par[x] = root(par[x])); }

struct Statement {
  int a, b;
  char op;
} sts[250000];

bool solve() {
  cin >> n >> m;
  for (int i = 0; i < m; i++) {
    cin >> sts[i].a >> sts[i].op >> sts[i].b;
  }
  for (int i = 0; i < n; i++) par[i] = i;
  for (int i = 0; i < m; i++) {
    if (sts[i].op != '=') continue;
    int a = sts[i].a, b = sts[i].b;
    a = root(a); b = root(b);
    par[b] = a;
  }
  for (int i = 0; i < m; i++) {
    if (sts[i].op == '=') continue;
    int a = sts[i].a, b = sts[i].b;
    if (sts[i].op == '<') swap(a, b);
    a = root(a); b = root(b);
    if (a == b) return false;
    adj[a].push_back(b);
    nin[b]++;
  }
  queue<int> q;
  for (int i = 0; i < n; i++) {
    if (par[i] != i) continue;
    if (nin[i] == 0) q.push(i);
  }
  int piv = 1;
  while (!q.empty()) {
    int u = q.front(); q.pop();
    ord[u] = piv++;
    for (int v: adj[u]) {
      nin[v]--;
      if (nin[v] == 0) q.push(v);
    }
  }
  for (int i = 0; i < n; i++) {
    if (par[i] != i) continue;
    if (ord[i] == 0) return false;
  }
  return true;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << (solve() ? "consistent" : "inconsistent") << '\n';
}
