#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

int n,m;
vector<int> edges[10000];
int power[10000];
bool visited[10000];

int ans[10000];
int ans_idx;

int main()
{
    scanf("%d%d", &n, &m);
    for(int i=0; i<m; ++i) {
        int a, b; 
        scanf("%d%d", &a, &b);
        --a; --b;
        edges[b].push_back(a);
    }
    for(int i=0; i<n; ++i) {
        for(int j=0; j<n; ++j) visited[j] = false;
        queue<int> Q;
        Q.push(i);
        visited[i] = true;
        while(!Q.empty()) {
            int u = Q.front(); Q.pop();
            for(int v: edges[u]) {
                if(visited[v]) continue;
                visited[v] = true;
                ++power[i];
                Q.push(v);
            }
        }
    }
    int max_power = -1;
    for(int i=0; i<n; ++i) {
        if(power[i] > max_power) {
            ans_idx = 1;
            ans[0] = i;
            max_power = power[i];
        } else if(power[i] == max_power) {
            ans[ans_idx++] = i;
        }
    }
    sort(ans, ans+ans_idx);
    for(int i=0; i<ans_idx; ++i) {
        printf("%d ", ans[i] + 1);
    }
}
