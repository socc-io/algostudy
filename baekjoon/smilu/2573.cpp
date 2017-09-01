#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int dir[4][2] = { 1, 0, -1, 0, 0, 1, 0, -1 };

int N, M;
int tile[300][300];
int tile2[300][300];
bool check[300][300];

void preceed()
{
    queue<pair<int,int>> Q;
    for(int x=1; x<N-1; ++x) {
        for(int y=1; y<M-1; ++y) {
            if(tile[x][y] > 0) {
                tile[x][y] -= tile2[x][y];
                if(tile[x][y] <= 0) {
                    Q.push(make_pair(x, y));
                    tile[x][y] = 0;
                }
            }
        }
    }
    while(!Q.empty()) {
        auto f = Q.front(); Q.pop();
        for(int i=0; i<4; ++i) {
            int nx = f.first + dir[i][0], ny = f.second + dir[i][1];
            tile2[nx][ny] += 1;
        }
    }
}

int check_one()
{
    int x, y;
    bool stop = false;
    for(x=0; x<N; ++x) for(y=0; y<M; ++y) check[x][y] = false;
    for(x=1; x<N-1; ++x) {
        for(y=1; y<M-1; ++y) {
            if(tile[x][y] > 0) {
                stop = true;
                break;
            }
        }
        if(stop) break;
    }
    if(!stop) return -1;
    queue<pair<int,int>> Q;
    Q.push(make_pair(x, y));
    check[x][y] = true;
    while(!Q.empty()) {
        auto f = Q.front(); Q.pop();
        for(int i=0; i<4; ++i) {
            int nx = f.first + dir[i][0], ny = f.second + dir[i][1];
            if(check[nx][ny] || tile[nx][ny] == 0)
                continue;
            check[nx][ny] = true;
            Q.push(make_pair(nx, ny));
        }
    }
    for(x=1; x<N-1; ++x) {
        for(y=1; y<M-1; ++y) {
            if(tile[x][y] > 0 && !check[x][y])
                return 0;
        }
    }
    return 1;
}

int main(void)
{
    cin >> N >> M;
    for(int i=0; i<N; ++i) {
        for(int j=0; j<M; ++j) {
            cin >> tile[i][j];
        }
    }
    for(int i=1; i<N-1; ++i) {
        for(int j=1; j<M-1; ++j) {
            tile2[i][j] = 0;
            for(int k=0; k<4; ++k) {
                int nx = i + dir[k][0], ny = j + dir[k][1];
                if(tile[nx][ny] == 0) ++tile2[i][j];
            }
        }
    }
    int res, ans = 0;
    while((res = check_one())) {
        if(res == -1) break;
        preceed();
        ++ans;
    }
    cout << (res == -1 ? 0 : ans);
}

