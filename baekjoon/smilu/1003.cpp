/*
 * https://www.acmicpc.net/problem/1003
 * author: smilu97
 */
#include <cstdio>
using namespace std;

#define MAX_POW 6

struct Matrix {
    int v[4];
    Matrix operator*(const Matrix& b) const {
        Matrix r;
        r.v[0] = v[0] * b.v[0] + v[1] * b.v[2];
        r.v[1] = v[0] * b.v[1] + v[1] * b.v[3];
        r.v[2] = v[2] * b.v[0] + v[3] * b.v[2];
        r.v[3] = v[2] * b.v[1] + v[3] * b.v[3];
        return r;
    }
    Matrix operator+(const Matrix& b) const {
        Matrix r;
        r.v[0] = v[0] + b.v[0];
        r.v[1] = v[1] + b.v[1];
        r.v[2] = v[2] + b.v[2];
        r.v[3] = v[3] + b.v[3];
        return r;
    }
};

Matrix base = { 0, 1, 1, 1 };
Matrix eye = { 1, 0, 0, 1 };

Matrix pows[MAX_POW];

int main(void)
{
    int T, N;
    Matrix r, t;

    pows[0] = base;
    for (int i = 1; i < MAX_POW; i++) {
        pows[i] = pows[i - 1] * pows[i - 1];
    }

    scanf("%d", &T);
    for (int i = 0; i < T; i++) {
        scanf("%d", &N);

        if (N == 0) {
            printf("1 0\n");
            continue;
        } else if (N == 1) {
            printf("0 1\n");
            continue;
        }

        N -= 1;
        r = eye;
        for (int j = 0; N; j++, N >>= 1) {
            if (N & 1) {
                t = r * pows[j];
                r = t;
            }
        }

        printf("%d %d\n", r.v[1], r.v[3]);
    }

    return 0;
}
