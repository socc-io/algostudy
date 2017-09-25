#include<iostream>
#include<vector>
#include<queue>
using namespace std;

#define INF 1234567890

struct node {
    int v, cost, time;
    node(int v=0, int cost=0, int time=0):v(v),cost(cost),time(time) {}
    bool operator<(const node &b) const {
        if(time == b.time) return cost > b.cost;
        return time > b.time;
    }
};

int n, m, k;
vector<node> adj[100];
int dp[100][10001];
bool inQ[100][10001];

int main()
{
    int Test;
    scanf("%d", &Test);
    while(Test--) {
        scanf("%d%d%d", &n, &m, &k);
        for(int i=0; i<n; ++i) {
            adj[i].clear();
        }
        for(int i=0; i<k; ++i) {
            int u, v, c, d;
            scanf("%d%d%d%d", &u, &v, &c, &d);
            --u; --v;
            adj[u].push_back(node(v, c, d));
        }
        for(int i=0; i<100; ++i) for(int j=0; j<10001; ++j) {
            dp[i][j] = INF;
            inQ[i][j] = false;
        }
        priority_queue<node> Q;
        Q.push(node(0, 0, 0));
        inQ[0][0] = true;
        dp[0][0] = 0;
        while(!Q.empty()) {
            node u = Q.top(); Q.pop();
            inQ[u.v][u.cost] = false;
            for(node e: adj[u.v]) {
                int new_cost = u.cost + e.cost;
                int new_time = u.time + e.time;
                if(new_cost > m) continue;
                if(new_time < dp[e.v][new_cost]) {
                    dp[e.v][new_cost] = new_time;
                    if(!inQ[e.v][new_cost]) {
                        inQ[e.v][new_cost] = true;
                        Q.push(node(e.v, new_cost, new_time));
                    }
                }
            }
        }
        bool succ = false;
        int min_time = INF;
        for(int i=0; i<=m; ++i) {
            min_time = min(min_time, dp[n-1][i]);
        }
        if(min_time == INF) {
            puts("Poor KCM");
        } else {
            printf("%d\n", min_time);
        }
    }
}
