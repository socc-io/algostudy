#include <bits/stdc++.h>
using namespace std;

typedef long long lld;

/**
 * Naive implementation of getting the number of combinations
 * of picking k items in n items
 */
lld comb(lld n, lld k) {
    lld r = 1;
    for (lld i = 1; i <= k; i++) {
        r *= n--;
        r /= i;
    }
    return r;
}

/**
 * Find any integer N which satisfies `comb(N, k) = m`.
 * If there is not any integer which satisfies this condition, returns -1.
 */
lld search_km(lld k, lld m) {
    // Find an arbitrary number N, which satisfies `comb(N, k) >= m`
    lld n_hi = 1;
    while (comb(n_hi, k) < m) {
        n_hi <<= 1;
    }

    // It is clear that `comb(n_hi / 2, k) < m`
    lld n_lo = n_hi >> 1;

    // Narrowen range (n_lo, n_hi) by using binary search
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

    // For now, `n_hi - n_lo <= 1`.
    // `n_lo`, `n_hi` are the only two integers which can exist between [n_lo, n_hi]

    if (comb(n_lo, k) == m) { // check `n_lo`
        return n_lo;
    }

    if (comb(n_hi, k) == m) { // check `n_hi
        return n_hi;
    }

    // The number n* which satisfies `comb(n*, k) = m` may not be an integer.
    return -1ll;
}

int main(void) {
    lld m; cin >> m;

    vector<pair<lld, lld>> ans;

    /**
     * We don't have to consider the k's which is bigger than 50.
     * Because we push another pair (n, n-k) when we have found a pair (n, k).
     * 
     * If we need to consider other cases even after pushing (n, n-k) pair, 
     * the maximum value of m must be bigger than comb(100, 50), which is tremendously
     * larger than our actual maximum value 10^15.
     */

    for (lld k = 1; k < 50; k++) {
        lld n = search_km(k, m);
        if (n == -1) continue;
        ans.push_back(make_pair(n, k));
        ans.push_back(make_pair(n, n-k));
    }

    sort(ans.begin(), ans.end()); // sort the candidates of answer
    ans.erase(unique(ans.begin(), ans.end()), ans.end()); // erase duplications

    // Print answers
    cout << ans.size() << '\n';
    for (auto p: ans) {
        cout << p.first << ' ' << p.second << '\n';
    }

    return 0;
}
