#include <bits/stdc++.h>
using namespace std;

int n, k;
int arr[1000];

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);
    sort(arr, arr + n);
    printf("%d", arr[n-k]);
}
