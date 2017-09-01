#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

inline int mmin(int a, int b) { return a < b ? a : b; }

int V, E;

vector<int> adj[10000];
vector<vector<int>> scc;
stack<int> S;
int level[10000];
int sccn[10000];
int level_idx;

int dfs(int cur)
{
    level[cur] = ++level_idx;
    S.push(cur);

    int res = level[cur];
    for(auto it = adj[cur].begin(); it != adj[cur].end(); ++it) {
        if(level[*it] == 0)
            res = mmin(res, dfs(*it));
        else if(sccn[*it] == -1)
            res = mmin(res, level[*it]);
    }
    if(res == level[cur]) {
        vector<int> nscc;
        while(1) {
            int t = S.top(); S.pop();
            nscc.push_back(t);
            sccn[t] = scc.size();
            if(t == cur) break;
        }
        sort(nscc.begin(), nscc.end());
        scc.push_back(nscc);
    }
    return res;
}

int main(void)
{
    scanf("%d%d", &V, &E);
    for(int i=0; i<E; ++i) {
        int a, b;
        scanf("%d%d", &a, &b);
        --a; --b;
        adj[a].push_back(b);
    }

    for(int i=0; i<V; ++i) {
        sccn[i] = -1;
    }

    for(int i=0; i<V; ++i) {
        if(level[i] == 0)
           dfs(i);
    }

    printf("%d\n", scc.size());
    sort(scc.begin(), scc.end());
    for(auto it = scc.begin(); it != scc.end(); ++it) {
        for(int v: (*it)) {
            printf("%d ", v+1);
        }
        puts("-1");
    }
}

