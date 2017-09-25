#include<iostream>
#include<vector>
#include<queue>
using namespace std;

typedef pair<int,int> pii;
#define INF 1234567890
#define MINF (-20000)

struct edge 
{
    int v, w;
    edge(int v=0, int w=0):v(v),w(w) {}
};

int n, m, w;
vector<edge> edges[500];
int minw[500];

int main()
{
    int Test;
    scanf("%d", &Test);
    while(Test--) {
        scanf("%d%d%d", &n, &m, &w);
        for(int i=0; i<n; ++i) {
            edges[i].clear();
        }
        for(int i=0; i<m; ++i) {
            int a, b, w;
            scanf("%d%d%d", &a, &b, &w);
            --a; --b;
            edges[a].push_back(edge(b, w));
            edges[b].push_back(edge(a, w));
        }
        for(int i=0; i<w; ++i) {
            int a, b, w;
            scanf("%d%d%d", &a, &b, &w);
            --a; --b;
            edges[a].push_back(edge(b, -w));
        }
        queue<int> Q;
        vector<bool> inQ(n, false);
        for(int i=0; i<n; ++i) {
            minw[i] = INF;
        }
        minw[0] = 0;
        Q.push(0);
        inQ[0] = true;
        while(!Q.empty()) {
            int u = Q.front();
            Q.pop();
            inQ[u] = false;
            for(edge e: edges[u]) {
                int new_w = minw[u] + e.w;
                if(new_w < minw[e.v]) {
                    if(new_w < 0 && minw[e.v] < 0) {
                        new_w = MINF;
                    }
                    if(!inQ[e.v] && minw[e.v] != MINF) {
                        Q.push(e.v);
                        inQ[e.v] = true;
                    }
                    minw[e.v] = new_w;
                }
            }
        }
        puts(minw[0] < 0 ? "YES" : "NO");
    }
}
