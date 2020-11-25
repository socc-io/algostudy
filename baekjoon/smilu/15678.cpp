#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int n, d;
ll arr[100010];
ll dp[100010];

deque<ll> q;
multiset<ll> s;
void push(ll x) {
    q.push_back(x);
    s.insert(x);
}
ll query() {
    return *s.rbegin();
}
void pop() {
    s.erase(s.find(q[0]));
    q.pop_front();
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n >> d;
    for (int i = 0; i < n; i++) cin >> arr[i];
    dp[n-1] = arr[n-1];
    push(arr[n-1]);
    for (int i = n-2; i >= 0; i--) {
        dp[i] = arr[i] + max(0ll, query());
        push(dp[i]);
        if (i < n-d) pop();
    }
    ll ans = *max_element(dp, dp + n);
    cout << ans << '\n';
}
