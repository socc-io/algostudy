#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

int n; // 1 <= n <= 200000
ll as[200020], bs[200020];
ll x[200020], xs[200020];
ll u[200020], us[200020];
ll d[200020], ds[200020];
ll uxs[200020];
ll dxs[200020];
ll muxs[200020], mdxs[200020];

ll solve() {
  cin >> n;
  for (int i = 0; i < n; i++) cin >> as[i];
  for (int i = 0; i < n; i++) cin >> bs[i];
  sort(as, as+n); sort(bs, bs+n);
  for (int i = 0; i < n; i++) x[i] = abs(as[i] - bs[i]);
  for (int i = 1; i <= n; i++) xs[i] = xs[i-1] + x[i-1];
  for (int i = 1; i < n; i++) u[i] = abs(as[i] - bs[i-1]);
  for (int i = 1; i <= n; i++) us[i] = us[i-1] + u[i-1];
  for (int i = 0; i < n-1; i++) d[i] = abs(as[i] - bs[i+1]);
  for (int i = 1; i <= n; i++) ds[i] = ds[i-1] + d[i-1];
  for (int i = 0; i <= n; i++) uxs[i] = us[i] - xs[i];
  for (int i = 0; i <= n; i++) dxs[i] = ds[i] - xs[i+1];
  muxs[n] = uxs[n];
  mdxs[n-1] = dxs[n-1];
  for (int i = n-1; i >= 0; i--) muxs[i] = min(uxs[i], muxs[i+1]);
  for (int i = n-2; i >= 0; i--) mdxs[i] = min(dxs[i], mdxs[i+1]);
  ll ans = 0x3f3f3f3f3f3f3f3f;
  for (int i = 0; i < n; i++) {
    ll ta = xs[i] - us[i+1] + xs[n] + muxs[i+1];
    ll tb = xs[i] - ds[i] + xs[n] + mdxs[i];
    ans = min(ans, min(ta, tb));
  }
  return ans;
}

int main(int argc, char** argv)
{
	int T, test_case;

	cin >> T;

	for(test_case = 0; test_case  < T; test_case++)
	{
		cout << "Case #" << test_case+1 << endl;
		cout << solve() << endl;
	}

	return 0;
}