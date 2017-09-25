#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

typedef pair<int,int> pii;
#define INF 1234567890

struct Edge
{
    int to, w;
    Edge(int to, int w):to(to), w(w) {}
};

int n;
vector<vector<Edge>> edges;
vector<int> dists;

int calc_dists(int src)
{
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    vector<bool> S(n, false);
    pq.push(make_pair(0, src));
    dists = vector<int>(n, INF);
    dists[src] = 0;
    while(!pq.empty()) {
        int u = pq.top().second; pq.pop();
        for(Edge e: edges[u]) {
            int new_dist = dists[u] + e.w;
            if(new_dist < dists[e.to]) {
                dists[e.to] = new_dist;
                pq.push(make_pair(new_dist, e.to));
            }
        }
    }
    return max_element(dists.begin(), dists.end()) - dists.begin();
}

int main()
{
    scanf("%d", &n);
    edges.resize(n);
    for(int i=0; i<n-1; ++i) {
        int a, b, w;
        scanf("%d%d%d", &a, &b, &w);
        --a; --b;
        edges[a].push_back(Edge(b, w)); 
        edges[b].push_back(Edge(a, w));
    }
    int max_idx = calc_dists(0);
    max_idx = calc_dists(max_idx);
    printf("%d", dists[max_idx]);
}
