#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pi;
typedef priority_queue<pi, vector<pi>, greater<pi>> gpq;

const int nears[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};
const int inf = 0x3f3f3f3f;

int N, T;
int grass[100][100];

bool in_farm(int x, int y) {
    return x >= 0 && x < N && y >= 0 && y < N;
}

struct Edge {
    int id;
    int time;
    Edge(int id, int time): id(id), time(time) {}
};

struct State {
    int e; // energy (max 3)
    int x, y; // coordination
    State(int e, int x, int y): e(e), x(x), y(y) {}
    State(int id) {
        e = id / 10000;
        id -= e * 10000;
        x = id / 100;
        id -= x * 100;
        y = id;
    }
    int get_id() const {
        return e * 10000 + x * 100 + y;
    }
    vector<Edge> get_nexts() {
        vector<Edge> edges;
        if (e > 0)  {
            int ne = e - 1;
            for (int ni = 0; ni < 4; ni++) {
                int nx = x + nears[ni][0];
                int ny = y + nears[ni][1];
                if (!in_farm(nx, ny)) continue;
                State next = State(ne, nx, ny);
                edges.push_back(Edge(next.get_id(), T));
            }
        } else {
            State ate = State(3, x, y);
            edges.push_back(Edge(ate.get_id(), grass[x][y]));
        }
        return edges;
    }
};

vector<int> do_dijkstra(int start_id) {
    vector<int> dist(40000, inf);
    vector<int> visit(40000, false);
    gpq q; // priority queue (greater)

    dist[start_id] = 0;
    q.push(make_pair(0, start_id));

    while (!q.empty()) {
        int u = q.top().second;
        q.pop();

        if (visit[u]) continue;
        visit[u] = true;

        for (Edge e: State(u).get_nexts()) {
            int v = e.id, t = e.time;
            if (visit[v]) continue;
            int new_vd = dist[u] + t;
            if (new_vd < dist[v]) {
                dist[v] = new_vd;
                q.push(make_pair(new_vd, v));
            }
        }
    }

    return dist;
}

int main(void) {
    ios::sync_with_stdio(0); cin.tie(0);

    // Input phase
    cin >> N >> T;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> grass[i][j];
        }
    }

    auto dist = do_dijkstra(State(3, 0, 0).get_id());

    int dest_1 = State(1, N-1, N-1).get_id();
    int dest_2 = dest_1 + 10000;
    int dest_3 = dest_2 + 10000;

    int answer = min(dist[dest_1], min(dist[dest_2], dist[dest_3]));

    printf("%d\n", answer);
}
