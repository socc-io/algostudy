#include<iostream>
#include<queue>
using namespace std;

int n, m;
int orig[500];
bool graph[500][500];
int indegree[500];

int main()
{
    int T;
    scanf("%d", &T);
    while(T--) {
        for(int i=0; i<500; ++i) {
            for(int j=0; j<500; ++j) {
                graph[i][j] = false;
            }
            orig[i] = 0;
            indegree[i] = 0;
        }
        scanf("%d", &n); 
        for(int i=0; i<n; ++i) scanf("%d", orig+i);
        for(int i=0; i<n; ++i) --orig[i];
        for(int i=0; i<n; ++i) {
           for(int j=i+1; j<n; ++j) {
              graph[orig[i]][orig[j]]=true;
              ++indegree[orig[j]];
           }
        }
        scanf("%d", &m);
        for(int i=0; i<m; ++i) {
            int a, b;
            scanf("%d%d", &a, &b);
            --a; --b;
            bool tmp = graph[a][b];
            graph[a][b] = !tmp;
            graph[b][a] = tmp;
            indegree[a] += tmp ? 1 : -1;
            indegree[b] += tmp ? -1 : 1;
        }
        queue<int> Q;
        for(int i=0; i<n; ++i) {
            if(indegree[i] == 0) {
                Q.push(i);
                break;
            }
        }
        bool succ = true;
        vector<int> ans(n);
        for(int i=0; i<n; ++i) {
            if(Q.empty()) {
                succ = false;
                break;
            }
            int f = Q.front(); Q.pop();
            ans[i] = f;
            for(int j=0; j<n; ++j) {
                if(graph[f][j]) {
                    --indegree[j];
                    if(indegree[j] == 0) {
                        Q.push(j);
                    }
                }
            }
        }
        if(succ) {
            for(int i=0; i<n; ++i) {
                printf("%d ", ans[i] + 1);
            }
        } else {
            printf("IMPOSSIBLE");
        }
        putchar('\n');
    }
}
