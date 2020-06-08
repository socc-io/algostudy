#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll mod = 1000000003;

int n, k;
ll mem[2][1000][1000];

ll dp(int use_first, int cnt_used, int last) {
  if (last < 0) {
    return use_first == 0 && cnt_used == 0;
  }
  if (last == 0) {
    return use_first == cnt_used;
  }
  if (cnt_used < 0) return 0;

  auto &ret = mem[use_first][cnt_used][last];
  if (ret != -1) return ret;

  ret = dp(use_first, cnt_used, last - 1);
  if (last != n-1 || !use_first) {
    ret += dp(use_first, cnt_used - 1, last - 2);
    ret %= mod;
  }

  return ret;
}

int main() {
  cin >> n >> k;
  memset(mem, 0xFF, sizeof(mem));
  cout << ((dp(0, k, n-1) + dp(1, k, n-1)) % mod) << '\n';
}
