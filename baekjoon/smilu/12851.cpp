/*
 * author: smilu97
 * description:
 *  algorithm solving of https://www.acmicpc.net/problem/12851
 */

#include <cstdio>
#include <queue>
#include <vector>
using namespace std;

#define INF 0x7FFFFFF0
#define MAX 100000

int main(void)
{
    int n, k;
    scanf("%d%d", &n, &k);
    queue<int> q;
    vector<int> c(MAX+1, INF); // costs
    vector<int> pc(MAX+1, 0); // path count
    q.push(n);
    c[n] = 0;
    pc[n] = 1;
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        int vs[3] = {u << 1, u + 1, u - 1};
        int nc = c[u] + 1; // next cost
        for (int i = 0; i < 3; i++) {
            int v = vs[i];
            if (v > MAX) continue;
            if (nc < c[v]) {
                c[v] = nc;
                q.push(v);
                pc[v] = pc[u];
            } else if (nc == c[v]) {
                pc[v] += pc[u];
            }
        }
    }
    printf("%d\n%d", c[k], pc[k]);
}
