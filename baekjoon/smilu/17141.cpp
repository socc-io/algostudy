/*
 * author: smilu97
 * description:
 *   algorithm solving: https://www.acmicpc.net/problem/17141
 */

#include <cstdio>
#include <cstdlib>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

#define INF 0x6FFFFFFF
typedef vector<vector<int>> vvi;

const int dd[4][2] = {
    {1, 0},
    {-1, 0},
    {0, 1},
    {0, -1},
};

int N, M, K;
vvi tile(50, vector<int>(50));

void print_vec(vector<int> & vec)
{
    for (auto v: vec) {
        if (v == INF) printf("UR ");
        else printf("%2d ", v);
    } puts("");
}

void get_costvec(vector<int> & vec, vvi & distmap)
{
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (tile[i][j] == 1) continue;
            vec.push_back(distmap[i][j]);
        }
    }
}

void get_distance_map(vvi & res, int x, int y)
{
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            res[i][j] = INF;  // clean with INF
        }
    }

    queue<pair<int,int>> Q;
    res[x][y] = 0;
    Q.push(make_pair(x, y));
    while(!Q.empty()) {
        auto u = Q.front();
        Q.pop();
        for (int i = 0; i < 4; i++) {
            int nx = u.first + dd[i][0];
            if (nx < 0 || nx >= N) continue;  // out bound
            int ny = u.second + dd[i][1];
            if (ny < 0 || ny >= N) continue;  // out bound

            if (tile[nx][ny] == 1) continue;  // wall
            if (res[nx][ny] != INF) continue;  // already visited

            res[nx][ny] = res[u.first][u.second] + 1;
            Q.push(make_pair(nx, ny));
        }
    }
}

int main(void)
{
    scanf("%d%d", &N, &M);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &tile[i][j]);
        }
    }

    vvi dist(N, vector<int>(N));
    vvi costvecs;
    for (int x = 0; x < N; x++) {
        for (int y = 0; y < N; y++) {
            if (tile[x][y] != 2) continue;
            get_distance_map(dist, x, y);
            vector<int> costvec;
            get_costvec(costvec, dist);
            costvecs.push_back(costvec);
        }
    }

    K = costvecs[0].size();
    vector<int> ind(K, 0);  // combination state
    vector<int> minvec(K);  // min_reduced costvecs
    int mincost = INF;
    for (int i = 0; i < M; i++) ind[i] = 1;
    sort(ind.begin(), ind.end());

    do {
        bool stop = false;
        for (int i = 0; i < K; i++) {
            minvec[i] = INF;
            for (int j = 0; j < costvecs.size(); j++) {
                if (!ind[j]) continue;
                if (minvec[i] > costvecs[j][i]) {
                    minvec[i] = costvecs[j][i];
                }
            }
            if (minvec[i] > mincost) {
                stop = true;
                break;
            }
        }
        if (stop) continue;
        int cost = -1;
        for (auto v: minvec) {
            if (cost < v) cost = v;
        }
        if (cost < mincost) mincost = cost;
    } while (next_permutation(ind.begin(), ind.end()));

    printf("%d\n", mincost == INF ? -1 : mincost);

    for (auto v: costvecs) {
        print_vec(v);
    }

    return 0;
}