#include <bits/stdc++.h>
using namespace std;

#define MAX 3000

typedef pair<int,int> pii;

int n, m, piv;

char pred[MAX];
vector<int> e[MAX];

int cnt, dfsn[MAX], SN, sn[MAX];
bool finished[MAX];
stack<int> S;
vector<vector<int>> scc;

void clear() {
  memset(pred, 0x00, sizeof(pred));
  for (int i = 0; i < MAX; i++) e[i].clear();
  cnt = 0;
  memset(dfsn, 0x00, sizeof(dfsn));
  SN = 0;
  memset(sn, 0x00, sizeof(sn));
  memset(finished, 0x00, sizeof(finished));
  while (!S.empty()) S.pop();
  scc.clear();
}

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

bool solve() {
  int i_res = scanf("%d%d", &n, &m);
  if (i_res == -1) return false;
  clear();
  piv = 2*n-1;
  for (int i = 0; i < m; i++) {
    int a, b; scanf("%d%d", &a, &b);
    a = get_index(a); b = get_index(b);
    e[piv - a].push_back(b);
    e[piv - b].push_back(a);
  }

  for(int i=0; i<2*n; i++)
    if(dfsn[i] == 0) find_scc(i);

  bool ans = true;
  for (int i = 0; i < n; i++) {
    if (sn[i] == sn[piv - i]) {
      ans = false;
      break;
    }
  }

  vector<pii> ps(n*2);
  for (int i = 0; i < n*2; i++) ps[i] = {sn[i], i};
  sort(ps.begin(), ps.end());
  
  for (int i=n*2-1; i >= 0; i--) {
    int u = ps[i].second;
    int ri = rev_index(u);
    if (pred[ri] == 0) pred[ri] = falsy(u) ? 1 : -1;
  }

  if (pred[0] < 0) ans = false;

  puts(ans ? "yes" : "no");
  
  return true;
}

int main() {
  while (solve());
}
