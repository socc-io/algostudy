#include<iostream>
#include<vector>
using namespace std;

#define TILE_MAX 2187

struct R {
    int a, b, c;
    R(int a=0, int b=0, int c=0):a(a),b(b),c(c) {}
    R operator+(const R &o) {
        return R(a+o.a, b+o.b, c+o.c);
    }
};

int n;
int tile[TILE_MAX][TILE_MAX];

R count(int sx, int sy, int ex, int ey)
{
    int aval = tile[sx][sy];
    bool fail = false;
    for(int x=sx; x<=ex; ++x) {
        for(int y=sy; y<=ey; ++y) {
            if(tile[x][y] != aval) {
                fail = true;
                break;
            }
        }
    }
    if(fail) {
        int dx = (ex-sx+1)/3;
        int dy = (ey-sy+1)/3;
        R sum;
        for(int i=0; i<3; ++i) for(int j=0; j<3; ++j) {
            sum = sum + count(sx + dx*i, sy + dy*j, sx + dx*(i+1)-1, sy + dy*(j+1)-1);
        }
        return sum;
    } else {
        if(aval == -1) return R(1, 0, 0);
        if(aval ==  0) return R(0, 1, 0);
                       return R(0, 0, 1);
    }
}

int main()
{
    scanf("%d", &n);
    for(int i=0; i<n; ++i) for(int j=0; j<n; ++j) {
        scanf("%d", tile[i]+j);
    }
    R res = count(0, 0, n-1, n-1);
    printf("%d\n%d\n%d", res.a, res.b, res.c);
}
