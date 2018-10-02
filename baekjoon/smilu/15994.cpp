#include <cstdio>
#include <queue>

using namespace std;

#define MAXN 50000000
#define MAXM 100

// #define DEBUG

struct Elev {
    int x; // From floor
    int y; // mult floor
    int b; // route-back
    int d;
    /*
     * Color flag-value
     * If 1) begin elev
     * If 2) end elev
     * If 3) begin, also end elev
     */
    int c;
    void input() {
        scanf("%d%d", &x, &y);
        --x;
    }
};

int N, M, A, B;
Elev elev[MAXM];
int C[MAXM][MAXM];

int min_dist, begin_elev;

inline void input()
{
    scanf("%d%d", &N, &M);
    for (int i = 0; i < M; i++) {
        elev[i].input();   
    }
    scanf("%d%d", &A, &B);
    --A, --B;
}

inline void output()
{
#ifdef DEBUG
    printf("begin_elev: %d\n", begin_elev);
#endif
    int cur = begin_elev;
    printf("%d\n%d\n", elev[begin_elev].d + 1, begin_elev + 1);
    while ((elev[cur].c & 2) == 0) {
        cur = elev[cur].b;
        printf("%d\n", cur + 1);
    }
}

int calc_conn(int a, int b);
inline void calc_conn_color()
{
    for (int i = 0; i < M; i++) {
        int x = elev[i].x, y = elev[i].y;
        if (x <= A && (A - x) % y == 0) {
            elev[i].c |= 1;
#ifdef DEBUG
            printf("Elev %d is START\n", i);
#endif
        }
        if (x <= B && (B - x) % y == 0) {
            elev[i].c |= 2;
#ifdef DEBUG
            printf("Elev %d is END\n", i);
#endif
        }
    }
    for (int i = 0; i < M; i++) {
        for (int j = i + 1; j < M; j++) {
            C[i][j] = calc_conn(i, j);
            C[j][i] = C[i][j];
        }
    }
}

inline int find_min_dist()
{
    queue<int> q;
    for (int i = 0; i < M; i++) {
        if (elev[i].c & 2) {
            q.push(i);
            elev[i].d = 0;
        } else {
            elev[i].d = -1;
        }
    }
    while(!q.empty()) {
        int u = q.front();
        q.pop();
#ifdef DEBUG
        printf("Visited %d\n", u);
#endif
        for (int v = 0; v < M; v++) {
            if (C[u][v] == 0) continue;
            if (elev[v].d != -1) continue;
#ifdef DEBUG
            printf("    Found %d\n", v);
#endif
            elev[v].d = elev[u].d + 1;
            elev[v].b = u;
            q.push(v);
            if (elev[v].c & 1) {
                begin_elev = v;
                return 1;
            }
        }
    }
    return 0;
}

int main(void)
{
#ifdef DEBUG
    printf("Debug mode activated\n");
#endif
    input();
    calc_conn_color();
    find_min_dist();
    output();

    return 0;
}

int calc_conn(int a, int b)
{
    for (int i = 0; i < elev[b].y; i++) {
        int v = elev[a].x + i * elev[a].y;
        if (v >= N) return 0;
        if ((v - elev[b].x) % elev[b].y == 0) {
#ifdef DEBUG
            printf("(%d, %d) is connected\n", a, b);
#endif
            return 1;
        }
    }
    return 0;
}