#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

bool tile[25][25];
int group_size[626];
int group_idx;
int n;

const int d[4][2] = {1, 0, -1, 0, 0, 1, 0, -1};

int visit(int x, int y)
{
    int ret = 1;
    tile[x][y] = 0;
    for(int k=0; k<4; ++k) {
        int nx = x + d[k][0], ny = y + d[k][1];
        if(nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
        if(tile[nx][ny] == 0) continue;
        ret += visit(nx, ny);
    }
    return ret;
}   

int main()
{
    scanf("%d", &n);
    for(int i=0; i<n; ++i) {
        getchar();
        for(int j=0; j<n; ++j) {
            tile[i][j] = getchar() == '1';
        }
    }
    group_idx = 0;
    for(int i=0; i<n; ++i) {
        for(int j=0; j<n; ++j) {
            if(tile[i][j] == 1) {
                group_size[group_idx++] = visit(i, j);
            }
        }
    }
    sort(group_size, group_size+group_idx);
    printf("%d\n", group_idx);
    for(int i=0; i<group_idx; ++i) {
        printf("%d\n", group_size[i]);
    }
}

