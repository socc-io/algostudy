#include <cstdio>
#include <queue>
#include <vector>
using namespace std;

#define MAX_WIDTH 100
#define MAX_HEIGHT MAX_WIDTH
#define NUM_TILE (MAX_WIDTH * MAX_HEIGHT)
#define INF 1234567890

#define EX(x) ((x) / width)
#define EY(x) ((x) % width)
#define CP(x, y) ((x) * width + (y))

typedef pair<int, int> iPair;

int width, height;
int dist[NUM_TILE];
int visited[NUM_TILE];
char tile[MAX_HEIGHT][MAX_WIDTH];

int dirs2[4][2] = {
    {1, 0},
    {-1, 0},
    {0, 1},
    {0, -1},
};
int dirs1[4] = { 0, 0, 1, -1 };

int main(void)
{
    scanf("%d%d", &width, &height);
    for (int i = 0; i < height; i++) {
        char* s = (char*)tile + (MAX_WIDTH * i);
        scanf("%s", s);
    }
    dirs1[0] = width;
    dirs1[1] = -width;

    for (int i = 0; i < NUM_TILE; i++) {
        dist[i] = INF;
    }

    priority_queue<iPair, vector<iPair>, greater<iPair> > q;
    q.push(make_pair(0, 0));
    dist[0] = 0;

    while(!q.empty()) {
        int u = q.top().second;
        int ux = EX(u);
        int uy = EY(u);
        int u_dist = dist[u];
        q.pop();
        if (visited[u]) continue;
        visited[u] = 1;
        for (int di = 0; di < 4; ++di) {
            int dx = dirs2[di][0];
            int dy = dirs2[di][1];
            int vx = ux + dx;
            int vy = uy + dy;
            if (vx < 0 || vx >= height ||
                vy < 0 || vy >= width) continue;
            int v = u + dirs1[di];
            int v_dist = u_dist + tile[vx][vy] - '0';
            if (v_dist < dist[v]) {
                dist[v] = v_dist;
                q.push(make_pair(v_dist, v));
            }
        }
    }

    printf("%d", dist[CP(width - 1, height - 1)]);

    return 0;
}