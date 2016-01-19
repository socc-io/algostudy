#include <stdio.h>

/*
 * good_s check function
 * return: 1 = good | 0 = bad
 */
int checkGoods(int *arr, int val, int current) {
    int i, j, to, flag;
    arr[current] = val;
    to = (current + 1) / 2;
    printf("  NOW\t\t| ");
    for (i=0; i<=current; i++) {
        printf("%d", arr[i]);
    }
    printf("\n");
    for (i=0; i<to; i++) {
        printf("  CHECK Lv.%d\t| ", i+1);
        flag = 0;
        for (j=0; j<=i; j++) printf("%d", arr[j]);
        printf(" <-> ");
        for (j=0; j<=i; j++) printf("%d", arr[to+j]);
        printf("\n");
        for (j=0; j<=i; j++) {
            printf("\t\t|   LEFT=%d RIGHT=%d\n", arr[current-(i+1)-j], arr[current-j]);
            if (arr[current-j] != arr[current-(i+1)-j]) flag = 1;
        }
        if (!flag) {
            printf("\t\t| [FAIL]\n");
            return 0;
        }
    }
    printf("\t\t| [SUCCESS]\n");
    return 1;
}

int pushElemToGoods(int *arr, int n, int current) {
    int i, next;
    next = current + 1;

    // end point of function
    if (current == n) {
        printf("---------------------------------------------\n");
        printf("ANSWER\t\t| ");
        for (i=0; i<n; i++) printf("%d", arr[i]);
        printf("\n");
        return 1;
    }

    for (i=1; i<=3; i++) {
        printf("TASK\t\t| INDEX=%d PUSH=%d\n", current, i);
        if (current == 0 || checkGoods(arr, i, current)) {
            arr[current] = i;
            if (pushElemToGoods(arr, n, next)) {
                return 1;
            }
        }
    }
    return 0;
}

/* main function */
int main(void) {
    int i, n, arr[80];

    // get n value
    scanf("%d", &n);

    // call makeGoods function
    pushElemToGoods(arr, n, 0);
}
