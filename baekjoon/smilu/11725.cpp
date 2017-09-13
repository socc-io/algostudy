#include<iostream>
#include<vector>
#include<queue>
using namespace std;

int n;
vector<vector<int>> edges;
vector<int> parent;

int main()
{
    scanf("%d", &n);
    edges.resize(n+1);
    parent.resize(n+1, -1);
    for(int i=0; i<n; ++i) {
        int a, b;
        scanf("%d%d", &a, &b); 
        edges[a].push_back(b);
        edges[b].push_back(a);
    }
    queue<int> Q;
    Q.push(1);
    while(!Q.empty()) {
        int u = Q.front(); Q.pop();
        for(int v: edges[u]) {
            if(parent[v] != -1) continue;
            parent[v] = u;
            Q.push(v);
        }
    }
    for(int i=2; i<=n; ++i) {
        printf("%d\n", parent[i]);
    }
}
