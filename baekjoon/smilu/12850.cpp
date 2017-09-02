#include <iostream>

using namespace std;

#define MATSIZE 8
#define MOD 1000000007LL
typedef long long matv;

struct matrix {
    matv v[MATSIZE][MATSIZE];
    matrix operator*(const matrix &b) {
        matrix res;
        for(int i=0; i<MATSIZE; ++i) {
            for(int j=0; j<MATSIZE; ++j) {
                res.v[i][j] = 0;
                for(int k=0; k<MATSIZE; ++k) {
                    res.v[i][j] += v[i][k] * b.v[k][j];
                }
                res.v[i][j] %= MOD;
            }
        }
        return res;
    }
    matrix operator+(const matrix &b) {
        matrix res;
        for(int i=0; i<MATSIZE; ++i) {
            for(int j=0; j<MATSIZE; ++j) {
                res.v[i][j] = (v[i][j] + b.v[i][j]) % MOD;
            }
        }
        return res;
    }
};

const matv map_matrix[8][8] = {
    {0, 1, 1, 0, 0, 0, 0, 0},
    {1, 0, 0, 1, 0, 0, 0, 0},
    {1, 0, 0, 1, 1, 0, 0, 0},
    {0, 1, 1, 0, 1, 1, 0, 0},
    {0, 0, 1, 1, 0, 1, 1, 0},
    {0, 0, 0, 1, 1, 0, 1, 1},
    {0, 0, 0, 0, 1, 1, 0, 1},
    {0, 0, 0, 0, 0, 1, 1, 0}
};

int main(void)
{
    int D;
    scanf("%d", &D);
    matrix a, m;
    for(int i=0; i<MATSIZE; ++i) {
        for(int j=0; j<MATSIZE; ++j) {
           a.v[i][j] = i == j;
           m.v[i][j] = map_matrix[i][j];
        }
    } 
    while(D) {
        if(D & 1) {
            a = a * m;
        }
        m = m * m;
        D >>= 1;
    }
    printf("%lld", a.v[7][7]);
}
