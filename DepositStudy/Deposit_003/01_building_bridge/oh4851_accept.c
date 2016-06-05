#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int i, j, n, m, testcase;
    int *result;

    scanf("%d", &testcase);
    result = (int *)malloc(sizeof(int)*testcase);
    for (i=0; i<testcase; i++) {
        scanf("%d %d", &n, &m);
        result[i] = 1;
        for (j=1; j<=n; j++) {
            result[i] = result[i] * (m-j+1) / j;
        }
    }
    for (i=0; i<testcase; i++) {
        printf("%d\n", result[i]);
    }

    free(result);
    return 0;
}
