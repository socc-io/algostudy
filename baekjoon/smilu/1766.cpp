#include<iostream>
#include<vector>
#include<queue>
using namespace std;

int n,m;
vector<int> edges[32000];
int degree[32000];

int main()
{
    scanf("%d%d", &n, &m);
    for(int i=0; i<m; ++i) {
        int a, b;
        scanf("%d%d", &a, &b);
        --a; --b;
        edges[a].push_back(b);
        ++degree[b];
    }
    priority_queue<int, vector<int>, greater<int>> pq;
    for(int i=0; i<n; ++i) {
        if(degree[i] == 0) {
            pq.push(i);
        }
    }
    while(!pq.empty()) {
        int u = pq.top(); pq.pop();
        printf("%d ", u+1);
        for(int v: edges[u]) {
            --degree[v];
            if(degree[v] == 0) {
                pq.push(v);
            }
        }
    }
}
