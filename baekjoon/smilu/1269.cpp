#include <bits/stdc++.h>
using namespace std;

int na, nb;
int arr[400000];

int main() {
    scanf("%d %d", &na, &nb);
    const int n = na + nb;
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);
    sort(arr, arr + n);
    
    int cd = 0;
    for (int i = 1; i < n; i++)
        cd += arr[i] == arr[i-1];
    
    printf("%d", n - (cd << 1));
}
