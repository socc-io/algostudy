#include "bits/stdc++.h"
using namespace std;

typedef vector<int> vi;

vi get_pi(vi s) {
  int n = s.size(), j = 0;
  vi pi(n, 0);
  for (int i = 1; i < n; i++) {
    while (j > 0 && s[i] != s[j]) j = pi[j-1];
    if (s[i] == s[j]) pi[i] = ++j;
  }
  return pi;
}

bool less(int ak, int ap, int as, int k, int p, int s) {
    return (s < as) || (s == as && p < ap);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;
    vi arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[n-1-i];
    }
    const vi pi = get_pi(arr);

    int ak = n-1, ap = 1, as = n;
    for (int i = 1; i < n; i++) {
        const int k = n-1-i;
        const int p = i+1-pi[i];
        const int s = k + p;
        if ((s < as) || (s == as && p < ap)) {
            ak = k;
            ap = p;
            as = s;
        }
    }

    cout << ak << ' ' << ap;
}
