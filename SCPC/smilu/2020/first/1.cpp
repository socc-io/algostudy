#include <iostream>
#include <algorithm>

using namespace std;

int n, k;
int as[200020], bs[200020];

int solve() {
  cin >> n >> k;
  for (int i = 0; i < n; i++) cin >> as[i];
  for (int i = 0; i < n; i++) cin >> bs[i];
  sort(as, as+n); sort(bs, bs+n);
  int ans = -1;
  for (int i = 0; i < k; i++) {
    ans = max(ans, as[i] + bs[k-1-i]);
  }
  return ans;
}

int main(int argc, char** argv)
{
  ios::sync_with_stdio(0); cin.tie(0);
	int T, test_case;

	cin >> T;
	for(test_case = 0; test_case  < T; test_case++)
	{
		cout << "Case #" << test_case+1 << endl;
		cout << solve() << endl;
	}

	return 0;//Your program should return 0 on normal termination.
}