#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int n, k;
ll sum[100010];
ll dp [100010];

deque<pair<ll,int>> deq;
void push(ll x, int i) {
    while (!deq.empty() && deq.back().first < x) deq.pop_back();
    deq.push_back({x, i});
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n >> k;;
    for (int i = 1; i <= n; i++) {
        ll tmp; cin >> tmp;
        sum[i] = sum[i-1] + tmp;
    }
    dp[0] = 0;
    dp[1] = sum[1];
    push(0, 0);
    push(-sum[1], 1);
    for (int i = 2; i <= n; i++) {
        while (deq.front().second < i-k) deq.pop_front();
        push(dp[i-1] - sum[i], i);
        dp[i] = deq.front().first + sum[i];
    }
    cout << dp[n] << '\n';
}
