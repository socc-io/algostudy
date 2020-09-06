#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <cassert>
#include <string>

using namespace std;

struct MaxSeg {
  vector<int> v;
  vector<int> lz;
  MaxSeg(): v(1<<18), lz(1<<18) {}
  void push(int n, int s, int e) {
    if (lz[n] == 0) return;
    if (s < e) {
      int l = n<<1, r = l | 1;
      lz[l] += lz[n];
      lz[r] += lz[n];
    }
    v[n] += lz[n];
    lz[n] = 0;
  }
  void update(int n, int s, int e, int f, int t, int uv) {
    push(n, s, e);
    if (t < s || e < f) return;
    if (f <= s && e <= t) {
      lz[n] += uv;
      push(n, s, e);
      return;
    }
    int m = (s+e)>>1, l = n<<1, r = l | 1;
    update(l, s, m, f, t, uv);
    update(r, m+1, e, f, t, uv);
    v[n] = max(v[l], v[r]);
  }
  int query(int n, int s, int e, int f, int t) {
    push(n, s, e);
    if (t < s || e < f) return 0;
    if (f <= s && e <= t) return v[n];
    int m = (s+e)>>1, l = n<<1, r = l | 1;
    return max(query(l,s,m,f,t), query(r,m+1,e,f,t));
  }
  const int auto_begin = 0;
  const int auto_end = (1<<17)-1;
  void update(int f, int t, int uv) { update(1, auto_begin, auto_end, f, t-1, uv); }
  int query(int f = 0, int t = (1<<17)) { return query(1, auto_begin, auto_end, f, t-1); }
};

int n; // t의 길이 1 <= n <= 50000
int k; // 부분문자열의 길이 1 <= k <= min(9, n)
int m; // 구간의 길이 0 <= m <= 1000000000 (10^9)
string t;

// naive: n(nk + nlogn)
// next: knlogn

int ans;

int get_value(int p, int q) {
  int res = 0;
  for (int i = p; i <= q; i++)
    res = res*10 + (t[i] - '0');
  return res;
}

void update_value(MaxSeg &seg, vector<int> &values, int s, int e, int uv) {
  const auto lo = lower_bound(values.begin(), values.end(), s) - values.begin();
  const auto up = upper_bound(values.begin(), values.end(), e) - values.begin();
  seg.update(lo, up, uv);
}

int solve() {
  cin >> n >> k >> m >> t;

  int num_values = n-k+1;
  vector<int> values; values.reserve(num_values);
  for (int i = 0; i < num_values; i++) {
    // if (t[i] == '0') continue;
    const int j = i + k - 1;
    values.push_back(get_value(i, j));
  }
  sort(values.begin(), values.end());
  num_values = values.size();

  MaxSeg seg;
  
  ans = -1;
  for (int i = 0; i < num_values; i++) {
    const auto lo = lower_bound(values.begin(), values.end(), values[i]);
    const auto up = upper_bound(values.begin(), values.end(), values[i] + m);
    const int cnt = up - lo;
    seg.update(i, i+1, cnt);
    ans = max(ans, cnt);
  }

  for (int i = 0; i < n; i++) {
    if (t[i] == '1') continue;
    char tmp = t[i];
    vector<int> erased_values; erased_values.reserve(k);
    for (int j = max(0, i-k+1); j <= min(i, n-k); j++) {
      // if (t[j] == '0') continue;
      const int value = get_value(j, j+k-1);
      update_value(seg, values, value - m, value, -1);
      erased_values.push_back(value);
    }
    sort(erased_values.begin(), erased_values.end());
    t[i] = '1';
    vector<int> new_values; new_values.reserve(k);
    for (int j = max(0, i-k+1); j <= min(i, n-k); j++) {
      // if (t[j] == '0') continue;
      const int value = get_value(j, j+k-1);
      update_value(seg, values, value - m, value, 1);
      new_values.push_back(value);
    }
    ans = max(ans, seg.query());
    sort(new_values.begin(), new_values.end());
    for (int j = 0; j < new_values.size(); j++) {
      const int value = new_values[i];
      auto lo = lower_bound(new_values.begin(), new_values.end(), value);
      auto up = upper_bound(new_values.begin(), new_values.end(), value + m);
      int cnt = up - lo;
      lo = lower_bound(values.begin(), values.end(), value);
      up = upper_bound(values.begin(), values.end(), value + m);
      cnt += up - lo;
      lo = lower_bound(erased_values.begin(), erased_values.end(), value);
      up = upper_bound(erased_values.begin(), erased_values.end(), value + m);
      cnt -= up - lo;
      ans = max(ans, cnt);
    }
    for (int j = max(0, i-k+1); j <= min(i, n-k); j++) {
      // if (t[j] == '0') continue;
      const int value = get_value(j, j+k-1);
      update_value(seg, values, value - m, value, -1);
    }
    t[i] = tmp;
    for (int j = max(0, i-k+1); j <= min(i, n-k); j++) {
      // if (t[j] == '0') continue;
      const int value = get_value(j, j+k-1);
      update_value(seg, values, value - m, value, 1);
    }
  }

  return ans;
}

int main(int argc, char** argv)
{
	int T, test_case;
  setbuf(stdout, NULL);

	cin >> T;
	for(test_case = 0; test_case  < T; test_case++)
	{
		cout << "Case #" << test_case+1 << endl;
		cout << solve() << endl;
	}

	return 0;
}