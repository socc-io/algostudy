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
  if (falsy(n)) return piv - v;
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
}
