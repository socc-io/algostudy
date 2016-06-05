#include <stdio.h>

int main(void) {
    int i;
    int num, result = 1;
    int digits[10] = {};

    for (i=0; i<3; i++) {
        scanf("%d", &num);
        result *= num;
    }
    i = 1;
    while (i < result) {
        i*= 10;
    }
    for (i=i/10; i>0; i/=10) {
        digits[result / i]++;
        result = result % i;
    }

    for (i=0; i<10; i++) {
        printf("%d\n", digits[i]);
    }

    return 0;
}
