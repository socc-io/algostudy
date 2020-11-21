#include <bits/stdc++.h>
using namespace std;

int n, m;
int hs[10];
bool not_prime[10100];
vector<int> ans;

void dfs(int index, int ticket, int sum_weight) {
    if (ticket <= 0) {
        if (!not_prime[sum_weight]) {
            ans.push_back(sum_weight);
        }
        return;
    }

    if (index < n) {
        dfs(index + 1, ticket, sum_weight);
        dfs(index + 1, ticket - 1, sum_weight + hs[index]);
    }
}

int main() {
    not_prime[0] = true;
    not_prime[1] = true;
    for (int i = 2; i < 10100; i++) {
        if (not_prime[i]) continue;
        for (int j = i*2; j < 10100; j += i) {
            not_prime[j] = true;
        }
    }

    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m;
    for (int i = 0; i < n; i++) cin >> hs[i];

    dfs(0, m, 0);
    sort(ans.begin(), ans.end());
    ans.erase(unique(ans.begin(), ans.end()), ans.end());
    for (int v: ans) cout << v << ' ';
    if (ans.size() == 0) cout << "-1";
}
