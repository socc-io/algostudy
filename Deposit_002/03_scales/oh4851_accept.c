#include <stdio.h>
#include <stdlib.h>

int n, half, cnt;

void merge_sort(int *data) {
    int i, j, mid, now;
    int *temp;
    temp = (int *)malloc(sizeof(int)*n);
    for (i=0; i<n; i++) {
        *(temp+i) = *(data+i);
    }
    mid = n/2;
    // left(insertion)
    for (i=1; i<mid; i++) {
        now = *(temp+i);
        j = i-1;
        while ((j>=0) && (*(temp+j) > now)) {
            *(temp+(j+1)) = *(temp+j);
            j--;
        }
        *(temp+(j+1)) = now;
    }
    // right(insertion)
    for (i=mid+1; i<n; i++) {
        now = *(temp+i);
        j = i-1;
        while ((j>=mid) && (*(temp+j) > now)) {
            *(temp+(j+1)) = *(temp+j);
            j--;
        }
        *(temp+(j+1)) = now;
    }
    // merge
    i = 0;
    j = mid;
    now = 0;

    while (i < mid && j < n) {
        if (*(temp+i) <= *(temp+j)) *(data+now++) = *(temp+i++);
        else *(data+now++) = *(temp+j++);
    }
    if (i < mid) {
        while (i < mid) {
            *(data+now++) = *(temp+i++);
        }
    }
    else if (j < n) {
        while (j < n) {
            *(data+now++) = *(temp+j++);
        }
    }

    free(temp);
}

void findAvailable(int *data, int sum, int idx) {
    int i;
    for (i=idx; i<n; i++) {
        if (sum+data[i] > half) break;
        else if (sum+data[i] == half) cnt++;
        else findAvailable(data, sum+data[i], i+1);
    }
}

int main(void) {
    int i, result;
    int *data;

    scanf("%d", &n);
    data = (int *)malloc(sizeof(int)*n);

    half = 0;
    for (i=0; i<n; i++) {
        scanf("%d", (data+i));
        half += *(data+i);
    }
    if (half%2 != 0) {
        printf("impossible\n");
        free(data);
        return 0;
    }
    // sort
    merge_sort(data);

    half /= 2;
    cnt = 0;
    // find (backtracking)
    findAvailable(data, 0, 0);

    if (cnt == 0) printf("impossible\n");
    else printf("%d\n", cnt);

    free(data);
    return 0;
}
