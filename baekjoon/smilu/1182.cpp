#include <stdio.h>

int sum_selection(int * arr, int len, int selection) {
    int result = 0;
    for (int position = 0; position < len; position++) {
        if ((selection & (1 << position))) {
            result += arr[position];
        }
    }
    return result;
}

int try_all_selections(int * arr, int len, int target) {
    int count = 0;
    int end = 1 << len;
    for (int selection = 1; selection < end; selection++) {
        count += (sum_selection(arr, len, selection) == target);
    }
    return count;
}

int arr[20];

int main() {
    int n, s;
    scanf("%d %d", &n, &s);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    printf("%d\n", try_all_selections(arr, n, s));
    return 0;
}
