#include<iostream>
#include<vector>
#include<queue>
using namespace std;

typedef pair<int,int> pii;

#define INF 900000

struct edge {
    int v, w;
    edge(int v=0, int w=0):v(v),w(w) {}
};

vector<edge> edges[800];
int minw[800];
int n, e;
int way[2];
int sdist[2][2];
int wayd;

void dijkstra(int src)
{
    priority_queue<pii, vector<pii>, greater<pii>> Q;
    for(int i=0; i<n; ++i) {
        minw[i] = INF;
    }
    Q.push(make_pair(0, src));
    minw[src] = 0;
    while(!Q.empty()) {
        int u = Q.top().second; Q.pop();
        for(edge e: edges[u]) {
            int new_w = minw[u] + e.w;
            if(new_w < minw[e.v]) {
                minw[e.v] = new_w;
                Q.push(make_pair(new_w, e.v));
            }
        }
    }
}


int main()
{
    scanf("%d%d", &n, &e);
    for(int i=0; i<e; ++i) {
        int a, b, w;
        scanf("%d%d%d", &a, &b, &w);
        --a; --b;
        edges[a].push_back(edge(b, w)); 
        edges[b].push_back(edge(a, w));
    }
    scanf("%d%d", way, way+1);
    --way[0];
    --way[1];
    dijkstra(0);
    sdist[0][0] = minw[way[0]];
    sdist[0][1] = minw[way[1]];
    dijkstra(n-1);
    sdist[1][0] = minw[way[0]];
    sdist[1][1] = minw[way[1]];
    dijkstra(way[0]);
    wayd = minw[way[1]];
    int ans = min(sdist[0][0] + sdist[1][1], sdist[0][1] + sdist[1][0]) + wayd;
    printf("%d", ans > INF ? -1 : ans);
}
