#include<iostream>
#include<vector>
using namespace std;

struct matrix
{
    vector<vector<int>> v;
    int n, m;
    matrix(int n, int m):v(n, vector<int>(m,0)), n(n), m(m) {}
    matrix operator*(const matrix &o) {
        matrix res(n, o.m);
        for(int i=0; i<n; ++i) {
            for(int j=0; j<o.m; ++j) {
                for(int k=0; k<m; ++k) {
                    res.v[i][j] += v[i][k] * o.v[k][j];
                }
            }
        }
        return res;
    }
    void input() {
        for(int i=0; i<n; ++i) {
            for(int j=0; j<m; ++j) {
                int tmp;
                scanf("%d", &tmp);
                v[i][j] = tmp;
            }
        }
    }
    void print() {
        for(int i=0; i<n; ++i) {
            for(int j=0; j<m; ++j) {
                printf("%d ", v[i][j]);
            }
            putchar('\n');
        }
    }
};

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    matrix a(n, m);
    a.input();
    scanf("%d%d", &n, &m);
    matrix b(n, m);
    b.input();
    matrix c = a*b;
    c.print();
}


