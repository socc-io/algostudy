#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;

struct edge {
    int node, c, d;
    edge(){}
    edge(int node, int c, int d):node(node),c(c),d(d) {}
    bool operator<(const edge &b) const {
        return d > b.d;
    }
};

int n, m, k;

vector<edge> edges[101];
int dist[101][10001];

void do_task()
{
    for(int i=0; i<101; ++i) for(int j=0; j<10001; ++j) dist[i][j] = 1234567890;
    scanf("%d%d%d", &n, &m, &k);
    for(int i=0; i<k; ++i) {
        int u, v, c, d;
        scanf("%d%d%d%d", &u, &v, &c, &d);
        edges[u].push_back(edge(v, c, d));
    }
    priority_queue<edge> pq;
    pq.push(edge(1, 0, 0));
    dist[1][0] = 0;
    while(!pq.empty()) {
        edge t = pq.top();
        pq.pop();
        if(t.node == n) continue;
        for(auto& e: edges[t.node]) {
            if(t.c + e.c > m) continue;
            if(t.d + e.d >= dist[e.node][t.c + e.c]) continue;
            dist[e.node][t.c + e.c] = t.d + e.d;
            pq.push(edge(e.node, t.c + e.c, t.d + e.d));
        }
    }
    int ans = *min_element(dist[n], dist[n] + 10001);
    if(ans == 1234567890) puts("Poor KCM");
    else printf("%d\n", ans);

    for(int i=0; i<n; ++i) edges[i].clear();
}

int main()
{
    int T;
    scanf("%d", &T);
    while(T--) do_task();
}