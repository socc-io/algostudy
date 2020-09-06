#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAX_N = 3003;

struct BIT {
  int ft[MAX_N];
  void update(int x, int v) {
    ft[x] = ft[x-1] + v;
    ft[x+1] = ft[x];
    // for (int i = x; i <= MAX_N; i+=(i&-i)) ft[i] += v;
  }
  int query(int a, int b) {
    return ft[b] - ft[a-1];
  }
} x_dp[3003], y_dp[3003];

int n, k;
int xv[3003], yv[3003];
int xs[3003], ys[3003];
int xd[3003], yd[3003];

bool getdp(int p1, int p2) {
  bool win = false;

  win |= x_dp[p2+1].query(xd[p1]+1, p1+1) > 0;
  win |= y_dp[p1+1].query(yd[p2]+1, p2+1) > 0;

  win |= (p1 == 0 && p2 == 0);

  x_dp[p2+1].update(p1+1, !win);
  y_dp[p1+1].update(p2+1, !win);

  return !win;
}

pair<int, int> solve() {
  cin >> n >> k;
  for (int i = 1; i <= n; i++) cin >> xv[i];
  for (int i = 1; i <= n; i++) cin >> yv[i];
  for (int i = 1; i <= n; i++) xs[i] = xs[i-1] + xv[i];
  for (int i = 1; i <= n; i++) ys[i] = ys[i-1] + yv[i];
  for (int i = 0; i <= n; i++) xd[i] = lower_bound(xs, xs+n, xs[i] - k) - xs;
  for (int i = 0; i <= n; i++) yd[i] = lower_bound(ys, ys+n, ys[i] - k) - ys;
  memset(x_dp, 0x00, sizeof(x_dp));
  memset(y_dp, 0x00, sizeof(y_dp));

  int cnt = 0;
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= n; j++) {
      cnt += getdp(i, j);
    }
  }

  return make_pair((n+1)*(n+1)-cnt, cnt);
}

int main(int argc, char** argv)
{
	int T, test_case;
  setbuf(stdout, NULL);

	cin >> T;
	for(test_case = 0; test_case  < T; test_case++)
	{
    auto ans = solve();
		cout << "Case #" << test_case+1 << '\n';
		cout << ans.first << ' ' << ans.second << '\n';
	}

	return 0;//Your program should return 0 on normal termination.
}