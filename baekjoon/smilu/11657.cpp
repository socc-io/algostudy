/*
 * author: smilu97
 * description:
 *   algorithm solving: https://www.acmicpc.net/problem/11657
 */

#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

#define INF 0x6FFFFFFF

struct Node {
    struct Edge {
        Node* node;
        int cost;
        Edge(Node* n, int c): node(n), cost(c) {}
    };
    int idx;
    vector<Edge*> edges;
    int d_cache;
    int visit_cnt;
    bool in_q;
};

bool SPFA(vector<Node*> & nodes, Node* start)
{
    int N = nodes.size();
    queue<Node*> q;
    for (auto node: nodes) {
        node->d_cache = INF;
        node->visit_cnt = 0;
        node->in_q = false;
    }

    start->d_cache = 0;
    q.push(start);
    start->in_q = true;
    while (!q.empty()) {
        Node* u = q.front();
        q.pop();
        u->in_q = false;
        for (auto edge: u->edges) {
            Node* v = edge->node;
            int new_d = u->d_cache + edge->cost;
            if (new_d < v->d_cache) {
                v->d_cache = new_d;
                if (v->visit_cnt >= N) {
                    return false;
                }
                if (!v->in_q) {
                    v->visit_cnt++;
                    q.push(v);
                    v->in_q = true;
                }
            }
        }
    }
    return true;
}

int main(void)
{
    int N, M;

    scanf("%d%d", &N, &M);
    
    vector<Node*> nodes(N);
    for (int i = 0; i < N; i++) {
        nodes[i] = new Node();
        nodes[i]->idx = i;
    }
    
    for (int i = 0; i < M; i++) {
        int A, B, C;
        scanf("%d%d%d", &A, &B, &C);
        nodes[A - 1]->edges.push_back(new Node::Edge(nodes[B - 1], C));
    }

    if (!SPFA(nodes, nodes[0])) {
        puts("-1");
        return 0;
    }

    for (int i = 1; i < N; i++) {
        printf("%d\n", nodes[i]->d_cache == INF ? -1 : nodes[i]->d_cache);
    }

    return 0;
}
