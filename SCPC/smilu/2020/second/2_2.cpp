#include <iostream>
#include <set>
#include <algorithm>

using namespace std;

typedef long long ll;

int n; // 1 <= n <= 300000
ll m; // 0 <= m <= 10^16
ll c[300030];
ll cs[300030];
set<ll> ss;

ll solve() {
  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> c[i];
  for (int i = 1; i <= n; i++) cs[i] = cs[i-1] + c[i-1];
  ll ans = 0;
  ss.clear();
  for (int j = 0; j <= n; j++) {
    ss.insert(cs[j]);
    auto it = ss.lower_bound(cs[j] - m);
    if (it == ss.end()) continue;
    ans = max(ans, cs[j] - (*it));
  }
  return ans;
}

int main(int argc, char** argv)
{
  setbuf(stdout, NULL);

	int T, test_case;

	cin >> T;
	for(test_case = 0; test_case  < T; test_case++)
	{
		// Print the answer to standard output(screen).
		cout << "Case #" << test_case+1 << endl;
		cout << solve() << endl;
	}

	return 0;
}