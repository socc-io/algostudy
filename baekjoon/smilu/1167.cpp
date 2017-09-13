#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

#define INF 0x7FFFFFF
typedef pair<int,int> pii;

struct edge
{
    int dest;
    int dist;
    edge(int dest=0, int dist=0):dest(dest),dist(dist) {}
};

int v;
vector<vector<edge>> edges;

pair<int,int> find_farest(int pos)
{
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    vector<int> dist(v, INF);
    dist[pos] = 0;
    pq.push(make_pair(0, pos));
    while(!pq.empty()) {
        int s = pq.top().second; pq.pop();
        for(edge e: edges[s]) {
            int nd = dist[s] + e.dist;
            if(nd < dist[e.dest]) {
                dist[e.dest] = nd;
                pq.push(make_pair(nd, e.dest));
            }
        }
    }
    int maxidx = max_element(dist.begin(), dist.end()) - dist.begin();
    return make_pair(maxidx, dist[maxidx]);
}

int main()
{
    scanf("%d", &v);
    edges.resize(v+1);
    for(int i=0; i<v; ++i) {
        int u, tmp, tmp2;
        scanf("%d", &u);
        --u;
        while(1) {
            scanf("%d", &tmp);
            if(tmp == -1) break;
            scanf("%d", &tmp2);
            edges[u].push_back(edge(tmp-1, tmp2));
        }
    }
    auto Q = find_farest(0);
    auto W = find_farest(Q.first); 
    printf("%d", W.second);
}
