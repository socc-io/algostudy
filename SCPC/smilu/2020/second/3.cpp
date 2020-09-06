#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <set>
#include <cassert>
#include <cstring>
using namespace std;

typedef long long ll;

struct MedianTracker {
  multiset<ll> s;
  multiset<ll>::iterator med;
  int cnt_left;
  int cnt_right;
  MedianTracker(ll *arr, int n) {
    s = multiset<ll>(arr, arr+n);
    med = s.begin();
    cnt_left = 0;
    cnt_right = n-1;
    _move();
  }
  ll median() {
    // for (auto v: s) cout << v << ' ';
    // cout << " : " << distance(s.begin(), med) << " : " << cnt_left << ", " << cnt_right << " : ";

    if (cnt_left == cnt_right) return *med;
    if (cnt_left < cnt_right) {
      auto r_med = med;
      ++r_med;
      return max(*med, *r_med);
    }
    auto l_med = med;
    --l_med;
    return max(*med, *l_med);
  }
  void _move() {
    while (cnt_left > cnt_right + 1) {
      --med;
      --cnt_left;
      ++cnt_right;
    }
    while (cnt_right > cnt_left + 1) {
      ++med;
      ++cnt_left;
      --cnt_right;
    }
  }
  void add(ll new_value) {
    if (med == s.end()) {
      s.insert(new_value);
      med = s.begin();
      return;
    }
    if (new_value < (*med)) {
      cnt_left++;
      s.insert(new_value);
    } else if (new_value >= (*med)) {
      cnt_right++;
      s.insert(new_value);
    }
    _move();
  }
  void remove(ll target_value) {
    assert(med != s.end());
    assert(!s.empty());
    if (med == s.end()) return;
    auto it = s.find(target_value);
    assert(it != s.end());
    if (it == med) {
      ++med;
      ++cnt_left;
      --cnt_right;
    }
    s.erase(it);
    if (med == s.end()) {
      if (!s.empty()) {
        --med;
        --cnt_left;
        ++cnt_right;
      }
    }
    if (s.empty()) {
      med = s.end();
      cnt_left = cnt_right = 0;
    } else if (med == s.end()) {
      --med;
      --cnt_left;
    } else if (target_value <= (*med)) {
      cnt_left--;
    } else {
      cnt_right--;
    }
    _move();
  }
};

int n, k, q;
ll ps[200020];
ll ls[200020];
ll arr[200020];

void solve() {
  scanf("%d%d%d", &n, &k, &q);
  for (int i = 0; i < n; i++) scanf("%lld", &ps[i]);
  
  memset(ls, 0x00, sizeof(ls));
  ll sum = 0;
  for (int i = 0; i < k-1; i++) sum += ps[i];
  for (int i = k-1; i < n; i++) {
    sum += ps[i];
    ls[i-k+1] = sum;
    sum -= ps[i-k+1];
  }
  // for (int i = 0; i < n-k+1; i++) cout << ls[i] << ' '; cout << '\n';

  for (int i = 0; i < n-k+1; i++) arr[i] = ls[i];
  MedianTracker med(arr, n-k+1);
  cout << med.median() << ' ';

  while (q--) {
    int a; ll b; scanf("%d%lld", &a, &b); --a;
    const int diff = b - ps[a];
    const int i_begin = max(0, a-k+1);
    const int i_end   = min(n-k+1, a+1);
    for (int i = i_begin; i < i_end; i++) {
      med.remove(ls[i]);
      ls[i] += diff;
      med.add(ls[i]);
    }
    ps[a] = b;
    // for (int i = 0; i < n-k+1; i++) cout << ls[i] << ' '; cout << '\n';
    cout << med.median() << ' ';
  }
  cout << '\n';
}

int main(int argc, char** argv)
{
  setbuf(stdout, NULL);
  ios::sync_with_stdio(0); cin.tie(0);

	int T, test_case;

	cin >> T;
	for(test_case = 0; test_case  < T; test_case++)
	{
		cout << "Case #" << test_case+1 << endl;
		solve();
	}

	return 0;//Your program should return 0 on normal termination.
}