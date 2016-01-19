#include <stdio.h>

#define WEIGHT_LIMIT 300

int getBinaryPosition(int value, int position) {
    int i;
    for (i=0; i<position; i++) {
        value = value >> 1;
    }
    return value & 0x00000001;}

int main(void) {
    int i, j, n, sum, ans, pow, cnt;  // 1 <= n <= 30
    int weights[30];

    cnt = 0;
    sum = 0;

    // data input
    scanf("%d", &n);
    for (i=0; i<n; i++) {
        scanf("%d", &weights[i]);
        sum += weights[i];
    }
    if (sum > WEIGHT_LIMIT) {
        printf("impossible\n");
        return 0;
    }
    if (sum % 2 != 0) {
        printf("impossible\n");
        return 0;
    }

    // get half of sum
    ans = sum / 2;

    // get power of weights length
    pow = 1;
    for (i=0; i<n; i++) pow *= 2;

    // find answer
    for (i=0; i<pow; i++) {
        sum = 0;
        for (j=0; j<n; j++) {
            sum += (weights[j] * getBinaryPosition(i, n-1-j));
            if (sum > ans) break;
        }
        if (sum == ans) cnt++;
    }
    printf("%d\n", cnt);
    
    return 0;
}
