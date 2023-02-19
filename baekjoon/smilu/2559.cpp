#include <bits/stdc++.h>
using namespace std;

int n, k;
int arr[100010];

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int loc_sum = 0;
    for (int i = 0; i < k-1; i++) {
        loc_sum += arr[i];
    }

    int ans = -0x3f3f3f3f;
    for (int i = k-1; i < n; i++) {
        loc_sum += arr[i];
        ans = max(ans, loc_sum);
        loc_sum -= arr[i-k+1];
    }

    printf("%d", ans);
}
