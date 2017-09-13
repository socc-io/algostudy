#include<iostream>
#include<vector>
using namespace std;

struct camp
{
    int x, y, r;
    camp(int x=0, int y=0, int r=0):x(x),y(y),r(r) { }
    bool with(camp &b) {
        int dx = x - b.x;
        int dy = y - b.y;
        int rs = r + b.r;
        return (dx*dx + dy*dy) <= rs*rs;
    }
};

vector<vector<int>> edges;
vector<camp> camps;
vector<bool> visit;
int group_num;

void find_group(int pos)
{
    visit[pos] = true;
    for(int next: edges[pos]) {
        if(visit[next]) continue;
        find_group(next);
    }
}

int main()
{
    int T;
    scanf("%d", &T);
    while(T--) {
        int n;
        scanf("%d", &n);
        camps = vector<camp>(n);
        edges = vector<vector<int>>(n);
        visit = vector<bool>(n, false);
        for(int i=0; i<n; ++i) {
            int x, y, r;
            scanf("%d%d%d", &x, &y, &r);
            camps[i] = camp(x, y, r);
        }
        for(int i=0; i<n; ++i) {
            for(int j=i+1; j<n; ++j) {
                if(camps[i].with(camps[j])) {
                    edges[i].push_back(j);
                    edges[j].push_back(i);
                }
            }
        }
        group_num = 0;
        for(int i=0; i<n; ++i) {
            if(!visit[i]) {
                find_group(i);
                ++group_num;
            }
        }
        printf("%d\n", group_num);
    }
}
