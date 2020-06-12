#include <cstdio>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;
const int MAX = 10000;
 
int V, E, cnt, dfsn[MAX], SN, sn[MAX];
vector<int> adj[MAX];
bool finished[MAX];
stack<int> S;
vector<vector<int>> SCC;

int DFS(int curr){
    dfsn[curr] = ++cnt;
    S.push(curr);
 
    int result = dfsn[curr];
    for(int next: adj[curr]) {
        if(dfsn[next] == 0) result = min(result, DFS(next));
        else if(!finished[next]) result = min(result, dfsn[next]);
    }
 
    if(result == dfsn[curr]){
        vector<int> currSCC;
        while(1){
            int t = S.top();
            S.pop();
            currSCC.push_back(t);
            finished[t] = true;
            sn[t] = SN;
            if(t == curr) break;
        }
        sort(currSCC.begin(), currSCC.end());
        SCC.push_back(currSCC);
        SN++;
    }
    return result;
}

int main(){
    scanf("%d %d", &V, &E);
    for(int i=0; i<E; i++){
        int A, B;
        scanf("%d %d", &A, &B);
        adj[A-1].push_back(B-1);
    }
 
    for(int i=0; i<V; i++)
        if(dfsn[i] == 0) DFS(i);
    sort(SCC.begin(), SCC.end());
 
    printf("%d\n", SN);
    for(auto& currSCC: SCC){
        for(int curr: currSCC)
            printf("%d ", curr+1);
        puts("-1");
    }
}

#include <bits/stdc++.h>
using namespace std;

class SCC: public vector<vector<int>> {
  vector<int> dfsn;
  vector<int> sn;
  vector<bool> finished;
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
  vector<int> execute() {
    piv = 0;
    sn.resize(n, 0);
    dfsn.resize(n, 0);
    finished.resize(n, false);
    while (!s.empty()) s.pop();
    for (int i = 0; i < n; i++) {
      if (dfsn[i] == 0) dfs(i);
    }
    return sn;
  }
  SCC(int n): n(n), adj(n) {}
};
