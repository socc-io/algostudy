#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

const int mod = 998244353;

typedef long long ll;

const ll l_inf = 0x3f3f3f3f3f3f3f3f;

using namespace std;

ll solve2(vector<vector<ll>> & mem, vector<pair<ll,ll>> & arr, int index, int m, int tr, int k) {
    const int n = arr.size();

    if (k < 0) return 0;

    if (index == tr) {
        return solve2(mem, arr, index+1, m, tr, k);
    }

    ll v = index < tr ? (arr[index].first + arr[index].second) : arr[index].first;

    if (index >= n-1 || (index == n-2 && tr == n-1)) {
        if (k == 1) return v;
        else if (k == 0) return m - v;
        return 0;
    }

    if (mem[index][k] != l_inf) return mem[index][k];

    ll result = (v * solve2(mem, arr, index+1, m, tr, k-1)) % mod;
    result += ((m - v) * solve2(mem, arr, index+1, m, tr, k)) % mod;
    result %= mod;

    return mem[index][k] = result;
}

vector<pair<ll,ll>> make_candidates(vector<vector<int>> & a, int thres) {
    const int n = a.size();
    vector<pair<ll,ll>> candidates(n);
    for (int i = 0; i < n; i++) {
        auto lo = lower_bound(a[i].begin(), a[i].end(), thres);
        auto up = upper_bound(a[i].begin(), a[i].end(), thres);
        
        ll lt = lo - a[i].begin();
        ll eq = up - lo;
        ll gt = a[i].end() - up;
        
        candidates[i] = make_pair(gt, eq);
    }
    return candidates;
}

ll solve(vector<pair<ll,ll>> & candidates, vector<vector<int>> & a, int target, int k) {
    const ll m = a[0].size(), n = a.size();
    vector<vector<ll>> mem(candidates.size(), vector<ll>(k, l_inf));
    return solve2(mem, candidates, 0, m, target, k-1);
}

vector<int> solution(int k, vector<vector<int>> a) {
    vector<int> answer;

    for (auto & row: a) sort(row.begin(), row.end());

    vector<vector<pair<ll,ll>>> candidates(1001);
    for (int i = 0; i < 1001; i++) {
        candidates[i] = make_candidates(a, i);
    }

    for (int i = 0; i < a.size(); i++) {
        ll result = 0;
        ll prev = 0;
        for (int j = 0; j < a[i].size(); j++) {
            if (j == 0 || a[i][j] != a[i][j-1]) {
                prev = solve(candidates[a[i][j]], a, i, k);
            }
            result = (result + prev) % mod;
        }
        answer.push_back(result);
    }

    return answer;
}

int main() {
    vector<vector<int>> a = {{1,1},{1,2},{1,2}};
    for (int v: solution(3, a)) {
        cout << v << ' ';
    } cout << '\n';
    return 0;
}
