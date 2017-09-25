#include<iostream>

using namespace std;

typedef int vtype;

#define MOD 15746

struct mat {
    vtype v[2][2];
    mat operator*(const mat &b) {
        mat res;
        for(int i=0; i<2; ++i) {
            for(int j=0; j<2; ++j) {
                res.v[i][j] = 0;
                for(int k=0; k<2; ++k) { 
                    res.v[i][j] += v[i][k] * b.v[k][j];
                }
                res.v[i][j] %= MOD;
            }
        }
        return res;
    }
};

int main(void)
{
    int n;
    scanf("%d", &n);
    mat r, b;
    r.v[0][0] = 1; r.v[0][1] = 0; r.v[1][0] = 0; r.v[1][1] = 1;
    b.v[0][0] = 0; b.v[0][1] = 1; b.v[1][0] = 1; b.v[1][1] = 1;
    while(n) {
        if(n & 1) {
            r = r*b;
        }
        b = b*b;
        n >>= 1;
    }
    printf("%d", (r.v[0][1] + r.v[0][0]) % MOD);
}

