#include<iostream>
#include<vector>
#include<queue>
using namespace std;

vector<int> edges[32001];
int indegree[32001];
int n, m;

int main()
{
    scanf("%d%d", &n, &m);
    for(int i=0; i<m; ++i) {
        int a, b;
        scanf("%d%d", &a, &b);
        edges[a].push_back(b);
        indegree[b]++;
    }
    queue<int> Q;
    for(int i=1; i<=n; ++i) {
        if(indegree[i] == 0) {
            Q.push(i);
        }
    }
    while(!Q.empty()) {
        int f = Q.front(); Q.pop();
        printf("%d ", f);
        for(int v: edges[f]) {
            --indegree[v];
            if(indegree[v] == 0) {
                Q.push(v);
            }
        }
    }
}
