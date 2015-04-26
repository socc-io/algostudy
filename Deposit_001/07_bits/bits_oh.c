#include <stdio.h>

int main(void) {
    int i, n, m;
    long long temp, sumBits = 0;
    scanf("%d %d", &n, &m);

    for (i=0; i<=m; i++) {
        if (i==0) temp = 1;
        else {
            temp = (n - i + 1) * temp / i;
        }
        sumBits += temp;
    }
    printf("%lld", sumBits);
    return 0;
}
