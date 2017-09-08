#include<iostream>
using namespace std;

typedef unsigned long long llu;
typedef signed long long lld;

#define MOD 1000000007

struct matrix {
    lld v[2][2];
    matrix operator*(const matrix &b) const {
        matrix res;
        for(int i=0; i<2; ++i) for(int j=0; j<2; ++j) {
            res.v[i][j] = 0;
            for(int k=0; k<2; ++k) {
                res.v[i][j] += v[i][k] * b.v[k][j];
                res.v[i][j] %= MOD;
            }
        }
        return res;
    }
    matrix operator^(lld k) const {
        matrix res = {1, 0, 0, 1};
        matrix mul = (*this);
        while(k) {
            if(k & 1) {
                res = res*mul;
            }
            k >>= 1;
            mul = mul*mul;
        }
        return res;
    }
};

const matrix base = {0, 1, 1, 1};

int main()
{
    lld n, m;
    scanf("%lld%lld", &n, &m);
    if(n<m) m = m%n;
    while(m) {
        lld tmp = n%m;
        n = m;
        m = tmp;
    }
    printf("%lld", (base^n).v[0][1]);
}

