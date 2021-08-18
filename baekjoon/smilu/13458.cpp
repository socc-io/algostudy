#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    vector<int> arr(n);
    
    for (int i = 0; i < n; i++) cin >> arr[i];

    int b, c;
    cin >> b >> c;

    long long ans = 0;
    for (int v: arr) {
        if (v <= b) ++ans;
        else ans += 1 + (v-b + c-1) / c;
    }
    
    cout << ans;
}
