#include<iostream>
#include<vector>
#include<queue>
using namespace std;

#define INF 1234567890

typedef pair<int,int> pii;

struct edge {
    int v, w;
    edge(int v=0, int w=0):v(v),w(w) {}
};

int v, e;
int src;
vector<edge> edges[20000];

int main()
{
    scanf("%d%d%d", &v, &e, &src); 
    --src;
    for(int i=0; i<e; ++i) {
        int a, b, w;
        scanf("%d%d%d", &a, &b, &w);
        --a; --b;
        edges[a].push_back(edge(b, w)); 
    }
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    vector<int> minw(v, INF);
    minw[src] = 0;
    pq.push(make_pair(0, src));
    while(!pq.empty()) {
        int u = pq.top().second; pq.pop();
        for(edge e: edges[u]) {
            int new_w = minw[u] + e.w;
            if(new_w < minw[e.v]) {
                minw[e.v] = new_w;
                pq.push(make_pair(new_w, e.v));
            }
        }
    }
    for(int i=0; i<v; ++i) {
        if(minw[i] == INF) {
            puts("INF");
        } else {
            printf("%d\n", minw[i]);
        }
    }
}
