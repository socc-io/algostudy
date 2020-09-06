#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

const int box_size = 700;

int n; // 1 <= n <= 300000
ll m; // 0 <= m <= 10^16
ll c[300030];
ll cs[300030];
pair<ll, int> box[box_size][box_size];

ll solve() {
  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> c[i];
  for (int i = 1; i <= n; i++) cs[i] = cs[i-1] + c[i-1];
  for (int i = 0; i <= n; i++) {
    const int bi = i / box_size;
    const int bj = i - bi * box_size;
    box[bi][bj] = make_pair(cs[i], i);
  }
  const int n5 = (n+1) / box_size;
  const int m5 = (n+1) - n5 * box_size;
  for (int i = 0; i < n5; i++) sort(box[i], box[i] + box_size);
  sort(box[n5], box[n5]+m5);

  ll ans = 0;
  for (int i = 0; i < n-1; i++) {
    const int i5 = i / box_size;
    const ll tv = cs[i] + m;
    const ll csi = cs[i];
    for (int j = 0; j < box_size; j++) {
      if (box[i5][j].second <= i) continue;
      ll tmp = box[i5][j].first - csi;
      if (tmp > m) continue;
      ans = max(ans, tmp);
    }
    for (int bi = i5+1; bi < n5; bi++) {
      auto it = lower_bound(box[bi], box[bi] + box_size, make_pair(tv, 0));
      if (it->first == tv) return m;
      --it;
      // printf("(%d, %d): %lld\n", i, it->second, it->first - csi);
      ans = max(ans, it->first - csi);
    }
    for (int j = 0; j < m5; j++) {
      // printf("(%d, %d): %lld\n", i, box[n5][j].second, box[n5][j].first - csi);
      if (box[n5][j].second <= i) continue;
      ll tmp = box[n5][j].first - csi;
      if (tmp > m) continue;
      ans = max(ans, tmp);
    }
  }

  return ans;
}

int main(int argc, char** argv)
{
  setbuf(stdout, NULL);
  ios::sync_with_stdio(0); cin.tie(0);

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