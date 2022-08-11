#include <bits/stdc++.h>
using namespace std;

typedef long long lld;

lld comb(lld n, lld k) {
    lld r = 1;
    for (lld i = 1; i <= k; i++) {
        r *= n--;
        r /= i;
    }
    return r;
}

lld search_km(lld k, lld m) {
    lld n_hi = 1;
    while (comb(n_hi, k) < m) {
        n_hi <<= 1;
    }

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
    lld m; cin >> m;

    vector<pair<lld, lld>> ans;
    for (lld k = 1; k < 50; k++) {
        lld n = search_km(k, m);
        if (n == -1) continue;
        ans.push_back(make_pair(n, k));
        ans.push_back(make_pair(n, n-k));
    }

    sort(ans.begin(), ans.end());
    ans.erase(unique(ans.begin(), ans.end()), ans.end());
    cout << ans.size() << '\n';
    for (auto p: ans) {
        cout << p.first << ' ' << p.second << '\n';
    }

    return 0;
}
