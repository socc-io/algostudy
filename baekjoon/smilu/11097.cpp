#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

vector<int> adj[300];
vector<vector<int>> scc;
vector<vector<bool>> sccc;
stack<int> S;
int sccn[300];
int level[300];
int level_idx;
int N;

int find_scc(int n)
{
    level[n] = level_idx++;
    S.push(n);

    int res = level[n];
    for(auto it = adj[n].begin(); it != adj[n].end(); ++it) {
        int v = *it;
        if(level[v] == -1) res = min(res, find_scc(v));
        else if(sccn[v] == -1) res = min(res, level[v]);
    }

    if(res == level[n]) {
        vector<int> nscc;
        while(1) {
            int t = S.top(); S.pop();
            nscc.push_back(t);
            sccn[t] = scc.size();
            if(t == n) break;
        }
        // sort(nscc.begin(), nscc.end());
        scc.push_back(nscc);
    }
    return res;
}


int main(void)
{
    int T;
    scanf("%d", &T); 
    while(T--) {
        scanf("%d", &N);
        // global initialize
        scc.clear();
        level_idx = 0;
        for(int i=0; i<N; ++i) {
            level[i] = -1;
            sccn[i] = -1;
            adj[i].clear();
        }
        while(!S.empty()) S.pop(); // make Stack empty
        // get inputs
        for(int i=0; i<N; ++i) {
            getchar();
            for(int j=0; j<N; ++j) {
                if(getchar() == '1' && i != j) {
                    adj[i].push_back(j);
                }
            }
        }
        // find scc
        for(int i=0; i<N; ++i) {
            if(level[i] == -1) find_scc(i);
        }
        // scc circuit
        puts("Circuits: ");
        for(auto it = scc.begin(); it != scc.end(); ++it) {
            int sz = it->size();
            for(int i=0; i<sz-1; ++i) {
                printf("%d %d\n", (*it)[i]+1, (*it)[i+1]+1);
            }
            if(sz > 1)  printf("%d %d\n", (*it)[sz-1]+1, (*it)[0]+1);
        }
        putchar('\n');
        // bridge beetween scc
        puts("Bridges: ");
        sccc.resize(scc.size(), vector<bool>(scc.size(), false));
        for(int i=0; i<N; ++i) {
            for(auto vit = adj[i].begin(); vit != adj[i].end(); ++vit) {
                int v = *vit;
                if(sccn[i] != sccn[v] && sccc[i][v] == false) {
                    sccc[i][v] = true;
                    printf("%d %d\n", i+1, v+1);
                }
            }
        }
        
    }
}
