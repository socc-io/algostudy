#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;

    vector<int> dp(n+1);

    for (int i = 1; i <= n; i++) {
        int d, c; cin >> d >> c;
        for(int j = i+d-1; j <= n; j++) {
            dp[j] = max(dp[j], dp[i-1] + c);
        }
    }

    cout << dp[n];
}
