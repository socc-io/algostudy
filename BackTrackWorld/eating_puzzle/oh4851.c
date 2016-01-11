#include <stdio.h>

int getBinaryPosition(int num, int position) {
    int i;
    for(i=0; i<position; i++) {
        num = num >> 1;
    }
    return num & 0x00000001;
}

int getBasketPower(int basket) {
    int i, result = 1;
    for (i=0; i<basket; i++) {
        result *= 2;
    }
    return result;
}

int main(void) {
    int i, j, sum, max;
    int limit, basket, pow, foods[21];

    scanf("%d %d", &limit, &basket);
    for (i=0; i<basket; i++) {
        scanf("%d", &foods[i]);
    }

    pow = getBasketPower(basket);

    max = 0;
    for (i=1; i<pow; i++) {
        sum = 0;
        for (j=0; j<basket; j++) {
            sum += (foods[j] * getBinaryPosition(i, basket-1-j));
        }
        if (sum > max && sum <= limit) max = sum;
    }
    printf("%d", max);

    return 0;
}
