#include<iostream>
#include<vector>
using namespace std;

#define INF 1234567890

vector<vector<int>> edges;
vector<bool> visited;
int n;
int dfss[100000][10];

int dfs(int root, int banned)
{
    if(dfss[root][banned-1]) return dfss[root][banned-1];
    visited[root] = true;
    int min_s = INF;
    int min_s_c;
    for(int c=1; c<=10; ++c) {
        if(c == banned) continue;
        int s = c;
        for(int next: edges[root]) {
            if(visited[next]) continue;
            s += dfs(next, c);
        }
        if(s < min_s) {
            min_s = s;
            min_s_c = c;
        }
    }
    visited[root] = false;
    dfss[root][banned-1] = min_s;
    return min_s;
}

int main()
{
    scanf("%d", &n);
    edges.resize(n);
    for(int i=0; i<n-1; ++i) {
        int a, b;
        scanf("%d%d", &a, &b);
        --a; --b;
        edges[a].push_back(b); 
        edges[b].push_back(a);
    }
    visited.resize(n, false);
    printf("%d", dfs(0, -1));
}
