#include<iostream>
#include<vector>
using namespace std;

typedef unsigned long long llu;

int n;
llu dp[100][100];

const int dd[2][2] = {1, 0, 0, 1};

int main()
{
    scanf("%d", &n);
    dp[0][0] = 1;
    for(int i=0; i<n; ++i) {
        for(int j=0; j<n; ++j) {
            int t, nx, ny;
            llu d = dp[i][j];
            scanf("%d", &t);
            if(t == 0) continue;
            for(int k=0; k<2; ++k) {
                nx = i + dd[k][0] * t;
                ny = j + dd[k][1] * t;
                if(nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
                dp[nx][ny] += d;
            }
        }
    }
    printf("%llu", dp[n-1][n-1]);
}
