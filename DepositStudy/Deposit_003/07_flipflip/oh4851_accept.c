#include <stdio.h>
#include <stdlib.h>

void swpSection(int* data, int left, int right) {
    int i, mid, temp;
    mid = (right-left)/2;
    for (i=0; i<=mid; i++) {
        temp = data[left+i];
        data[left+i] = data[right-i];
        data[right-i] = temp;
    }
}
int chkForward(int* input, int n) {
    int i, j, cnt;
    int left[2] = {1, 1}, right[2] = {1, 1};
    int *data;
    data = (int *)malloc(sizeof(int)*(n+1));
    for (i=1; i<=n; i++) {
        data[i] = input[i];
    }
    
    cnt = 0;
    for (i=1; i<n; i++) {
        if (data[i] != i) {
            for (j=i+1; j<=n; j++) {
                if (data[j] == i) break;
            }
            swpSection(data, i, j);
            left[cnt] = i;
            right[cnt++] = j;
        }
        if (cnt > 2) {
            free(data);
            return 0;
        }
    }
    for (i=0; i<2; i++) {
        printf("%d %d\n", left[i], right[i]);
    }
    free(data);
    return 1;
}
void chkReverse(int* input, int n) {
    int i, j, cnt;
    int left[2] = {1, 1}, right[2] = {1, 1};
    int *data;
    data = (int *)malloc(sizeof(int)*(n+1));
    for (i=1; i<=n; i++) {
        data[i] = input[i];
    }

    cnt = 0;
    for (j=n; j>1; j--) {
        if (data[j] != j) {
            for (i=j-1; i>=1; i--) {
                if (data[i] == j) break;
            }
            swpSection(data, i, j);
            left[cnt] = i;
            right[cnt++] = j;
        }
    }
    for (i=0; i<2; i++) {
        printf("%d %d\n", left[i], right[i]);
    }
    free(data);
}

int main(void) {
    int i, n;
    int *data;

    scanf("%d", &n);
    data = (int *)malloc(sizeof(int)*(n+1));

    for (i=1; i<=n; i++) {
        scanf("%d", &data[i]);
    }
    // forward
    if (!chkForward(data, n)) {
        chkReverse(data, n);
    }

    free(data);
    return 0;
}
