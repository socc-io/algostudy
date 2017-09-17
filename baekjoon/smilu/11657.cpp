#include<iostream>
#include<vector>
#include<queue>
using namespace std;

#define INF  ( 5000001)
#define MINF (-5000001)

struct edge {
    int v,w;
    edge(int v=0, int w=0):v(v),w(w) {}
};

int n, m;
vector<edge> edges[500];

int main()
{
    scanf("%d%d", &n, &m);
    for(int i=0; i<m; ++i) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        --a; --b;
        edges[a].push_back(edge(b, c));
    }
    queue<int> Q;
    vector<bool> inQ(n, false);
    vector<int> mdist(n, INF);
    Q.push(0);
    inQ[0] = true;
    mdist[0] = 0;
    while(!Q.empty()) {
        int f = Q.front(); Q.pop();
        inQ[f] = false;
        for(edge e: edges[f]) {
            int new_w = mdist[f] + e.w;
            if(new_w < mdist[e.v]) {
                if(new_w < 0 && mdist[e.v] < 0) {
                    puts("-1");
                    return 0;
                }
                if(!inQ[e.v]) {
                    Q.push(e.v);
                    inQ[e.v] = true;
                }
                mdist[e.v] = new_w;
            }
        }
    }
    for(int i=1; i<n; ++i) {
        printf("%d\n", mdist[i] != INF ? mdist[i] : -1);
    }
}
