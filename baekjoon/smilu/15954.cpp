#include <cstdio>
#include <cmath>

int a[500];
int N, K;
double minv = -1;

double variance(int* arr, int n)
{
    double s = 0;
    for (int i = 0; i < n; ++i) {
        s += arr[i];
    }
    double m = s / n;
    double v = 0;
    for (int i = 0; i < n; ++i) {
        double tmp = m - arr[i];
        v += tmp * tmp;
    }
    return v / n;
}

int main(void)
{
    scanf("%d%d", &N, &K);
    for (int i = 0; i < N; i++) {
        scanf("%d", a + i);
    }
    for (int i = 0; i < N; i++) {
        for (int j = i + K; j <= N; j++) {
            double v = variance(a + i, j - i);
            if (v < minv || minv == -1) {
                minv = v;
            }
        }
    }
    printf("%.11lf\n", sqrt(minv));

    return 0;
}