#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

const int MAX_N = 250000;
const int MAX_N_2 = MAX_N * 2;

int n, n2;
pi plates[MAX_N];
int zip[MAX_N_2], zn;

int par[MAX_N_2];
bool cyc[MAX_N_2];
int mxv[MAX_N_2];
ll sum[MAX_N_2];

int root(int x) { return x == par[x] ? x : (par[x] = root(par[x])); }

int main(void)
{
  ios::sync_with_stdio(0); cin.tie(0);
  cin >> n; n2 = n << 1;
  for (int i = 0; i < n; i++)
    cin >> plates[i].first
        >> plates[i].second;

  for (int i = 0; i < n; i++) zip[  i] = plates[i].first;
  for (int i = 0; i < n; i++) zip[n+i] = plates[i].second;
  sort(zip, zip + n2);
  zn = unique(zip, zip + n2) - zip;

  for (int i = 0; i < zn; i++) par[i] = i;
  for (int i = 0; i < zn; i++) cyc[i] = true;
  for (int i = 0; i < zn; i++) mxv[i] = zip[i];
  for (int i = 0; i < zn; i++) sum[i] = zip[i];

  for (int i = 0; i < n; i++) {
    const int a = root(lower_bound(zip, zip + zn, plates[i].first) - zip);
    const int b = root(lower_bound(zip, zip + zn, plates[i].second) - zip);
    if (a == b) {
      cyc[a] = false;
    } else {
      par[b] = a;
      cyc[a] &= cyc[b];
      mxv[a] = max(mxv[a], mxv[b]);
      sum[a] += sum[b];
    }
  }

  ll ans = 0;
  for (int i = 0; i < n; i++)
    ans += plates[i].first + plates[i].second;
  for (int i = 0; i < zn; i++) if (par[i] == i) {
    ans -= sum[i] - cyc[i] * mxv[i];
  }
  cout << ans << '\n';
}
