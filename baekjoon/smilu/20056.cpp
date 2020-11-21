#include <bits/stdc++.h>
using namespace std;

const int dirs[8][2] = {
    {-1,0},{-1,1},{0,1},{1,1},
    {1,0},{1,-1},{0,-1},{-1,-1}
};
const int split_dirs[2][4] = {
    {0,2,4,6},
    {1,3,5,7}
};

int n;

struct Fireball {
    int m, s, d;
    Fireball(int m, int s, int d): m(m),s(s),d(d) {}
};

Fireball sum_fireballs(const vector<Fireball> & fs) {
    Fireball res = Fireball(0, 0, 0);
    for (const auto & f: fs) {
        res.m += f.m;
        res.s += f.s;
    }
    return res;
}

bool every_even(const vector<Fireball> & fs) {
    for (const auto & f: fs) if (f.d & 1) return false;
    return true;
}

bool every_odd(const vector<Fireball> & fs) {
    for (const auto & f: fs) if (!(f.d & 1)) return false;
    return true;
}

auto get_split_dirs(const vector<Fireball> & fs) {
    return (every_even(fs) || every_odd(fs)) ? split_dirs[0] : split_dirs[1];
}

int adjust_range(int v) {
    return ((v % n) + n) % n;
}

struct Context {
    vector<Fireball> fireballs_at[50][50];
    void clear() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                fireballs_at[i][j].clear();
            }
        }
    }
    static void move_fireball(const int x, const int y, const Fireball & fb_src, Context & target) {
        const int speed = fb_src.s;
        const int * dir = dirs[fb_src.d];
        const int nx = adjust_range(x + dir[0] * speed);
        const int ny = adjust_range(y + dir[1] * speed);
        target.fireballs_at[nx][ny].push_back(fb_src);
    }
    void process_collision_at(const int x, const int y) {
        auto & fireballs = fireballs_at[x][y];
        if (fireballs.size() <= 1) return;
        const auto merged = sum_fireballs(fireballs);
        const auto s_dirs = get_split_dirs(fireballs);
        const int m = merged.m / 5;
        const int s = merged.s / fireballs.size();
        fireballs.clear();
        if (m > 0) {
            for (int i = 0; i < 4; i++) {
                fireballs.push_back(Fireball(m, s, s_dirs[i]));
            }
        }
    }
    void process_collision() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                process_collision_at(i, j);
            }
        }
    }
    void next(Context &target) {
        target.clear();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (const auto & fireball: fireballs_at[i][j]) {
                    move_fireball(i, j, fireball, target);
                }
            }
        }
        target.process_collision();
    }
    int sum_m() {
        int m = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (const auto & f: fireballs_at[i][j]) {
                    m += f.m;
                }
            }
        }
        return m;
    }
};

Context contexts[2];

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int num, k;
    cin >> n >> num >> k;
    for (int i = 0; i < num; i++) {
        int x, y; cin >> x >> y;
        int m, s, d; cin >> m >> s >> d;
        --x; --y;
        contexts[0].fireballs_at[x][y].push_back(Fireball(m, s, d));
    }
    int pivot = 0;
    for (int i = 0; i < k; i++) {
        contexts[pivot].next(contexts[1 - pivot]);
        pivot = 1 - pivot;
    }
    printf("%d\n", contexts[pivot].sum_m());
}
