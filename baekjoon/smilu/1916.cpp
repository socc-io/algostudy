#include <cstdio>

#include <vector>
#include <queue>

using namespace std;

typedef pair<int,int> iPair;

#define MAXN 1000
#define MAXM 100000
#define INF 1234567890

struct Edge {
    int from;
    int to;
    int weight;
    Edge(int from, int to, int weight):
        from(from), to(to), weight(weight) {}
};

struct Node {
    int idx;
    vector<Edge> edges;
    int distance;
    int visited;
};

int N, M;
int g_start, g_end;
Node g_nodes[MAXN];

int main(void)
{
    scanf("%d%d", &N, &M);
    for (int i = 0; i < M; i++) {
        int from, to, weight;
        scanf("%d%d%d", &from, &to, &weight);
        --from, --to;
        g_nodes[from].edges.push_back(Edge(from, to, weight ));
    }
    scanf("%d%d", &g_start, &g_end);
    --g_start, --g_end;

    for (int i = 0; i < N; i++) {
        g_nodes[i].distance = INF;
        g_nodes[i].idx = i;
        g_nodes[i].visited = 0;
    }

    priority_queue<iPair, vector<iPair>, greater<iPair> > q;
    q.push(make_pair(0, g_start));
    g_nodes[g_start].distance = 0;

    while(!q.empty()) {
        int u = q.top().second;
        q.pop();
        Node* U = g_nodes + u;
        if (U->visited == 1) continue;
        U->visited = 1;
        for (auto it = U->edges.begin(); it != U->edges.end(); ++it) {
            int v = it->to;
            int w = it->weight;
            Node* V = g_nodes + v;
            int new_distance = U->distance + w;
            if (new_distance < V->distance) {
                V->distance = new_distance;
                q.push(make_pair(new_distance, v));
            }
        }
    }

    printf("%d", g_nodes[g_end].distance);

    return 0;
}