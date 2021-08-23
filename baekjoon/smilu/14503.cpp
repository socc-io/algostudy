#include <bits/stdc++.h>
using namespace std;

const int dd[4][2] = {
    {-1, 0}, {0, 1}, {1, 0}, {0, -1},
};

struct Env {
    int n, m;
    vector< vector<bool> > dirty;
    vector< vector<bool> > wall;
    Env(int n, int m):
        n(n),
        m(m),
        dirty(n, vector<bool>(m, true)),
        wall(n, vector<bool>(m, true))
    {}
};

struct Robot {
    Env * env;
    int x, y, dir;
    int score;
    Robot(Env * env, int x, int y, int dir): env(env), x(x), y(y), dir(dir), score(0) {}

    void Clean() {
        score += env->dirty[x][y];
        env->dirty[x][y] = false;
    }

    bool Move(int s) {
        int nx = x + dd[dir][0]*s, ny = y + dd[dir][1]*s;
        if (nx < 0 || nx >= env->n || ny < 0 || ny >= env->m) return false;
        if (env->wall[nx][ny]) return false;
        x = nx, y = ny;
        return true;
    }

    bool CheckDirection(int d) {
        int nx = x + dd[d][0], ny = y + dd[d][1];
        if (nx < 0 || nx >= env->n || ny < 0 || ny >= env->m) return false;
        if (env->wall[nx][ny]) return false;
        return env->dirty[nx][ny];
    }

    void Run() {
        for (;;) {
            Clean();

            int td = -1;
            for (int i = 1; i <= 4; i++) {
                int nd = (dir + 3*i) % 4;
                if (CheckDirection(nd)) {
                    td = nd;
                    break;
                }
            }

            if (td == -1) {
                if (false == Move(-1))
                    break;
            } else {
                dir = td;
                Move(1);
            }
        }
    }
};

int main() {
    int n, m; cin >> n >> m;
    Env env(n, m);

    int x, y, d; cin >> x >> y >> d;
    Robot robot(&env, x, y, d);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int v; cin >> v;
            env.wall[i][j] = v ? true : false;
        }
    }

    robot.Run();

    cout << robot.score;

    return 0;
}
