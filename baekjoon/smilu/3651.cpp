#include <bits/stdc++.h>
using namespace std;

typedef long long lld;

lld comb_cache[1000][50];

lld comb(lld n, lld k) {
    if (k > n) return 0ll;
    if (k == 0) return 1ll;
    int &r = comb_cache[n][k];
    return r = comb(n, k-1) + comb(n-1, k-1);
}

lld search_km(lld k, lld m) {
    lld n_hi = 1;
    while (comb(n_hi, k) < m) n_hi <<= 1;

    lld n_lo = n_hi >> 1;

    while (n_hi - n_lo > 1) {
        lld n_mid = (n_lo + n_hi) >> 1;
        lld piv = comb(n_mid, k);
        if (piv > m) {
            n_hi = n_mid - 1;
        } else if (piv < m) {
            n_lo = n_mid + 1;
        } else {
            return n_mid;
        }
    }

    if (comb(n_lo, k) == m) {
        return n_lo;
    }

    if (comb(n_hi, k) == m) {
        return n_hi;
    }

    return -1ll;
}

int main(void) {
    vector<pair<lld, lld>> ans;

    lld m; cin >> m;

    ans.push_back(make_pair(m, 1));
    ans.push_back(make_pair(m, m-1));

    for (lld k = 2; k < 50; k++) {
        lld n = search_km(k, m);
        if (n == -1) continue;
        ans.push_back(make_pair(n, k));
    }

    sort(ans.begin(), ans.end());
    ans.erase(unique(ans.begin(), ans.end()), ans.end());

    cout << ans.size() << '\n';
    for (auto p: ans) {
        cout << p.first << ' ' << p.second << '\n';
    }

    return 0;
}
