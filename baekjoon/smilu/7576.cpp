#include<iostream>
#include<vector>
#include<queue>
using namespace std;

int m, n;
int C[1000][1000];
int age[1000][1000];

struct position {
    int x, y;
    position(int x=0, int y=0):x(x), y(y) {}
    position operator+(const position &b) const {
        return position(x+b.x, y+b.y);
    }
    bool inbound() {
        return 0 <= x && x < n && 0 <= y && y < m;
    }
};

const position dd[4] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

int main()
{
    scanf("%d%d", &m, &n);
    queue<position> Q;
    for(int i=0; i<n; ++i) for(int j=0; j<m; ++j) {
        scanf("%d", C[i] + j);
        if(C[i][j] == 1) {
            Q.push(position(i, j));
        }
    }
    int max_age = -1;
    while(!Q.empty()) {
        position now = Q.front(); Q.pop();
        int now_age = age[now.x][now.y];
        max_age = max(max_age, now_age);
        for(int k=0; k<4; ++k) {
            position next = now + dd[k];
            if(!next.inbound()) continue;
            if(C[next.x][next.y] == -1) continue; 
            if(C[next.x][next.y] == 1) continue;
            C[next.x][next.y] = 1;
            age[next.x][next.y] = now_age + 1;
            Q.push(next);
        }
    }
    for(int i=0; i<n; ++i) for(int j=0; j<m; ++j) {
        if(C[i][j] == 0) {
            puts("-1");
            return 0;
        }
    }
    printf("%d", max_age);
}
