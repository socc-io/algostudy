#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int n, k;
char arr_s[15][51];
int arr[15];
int len[15];
int p10[1000];

ll gcd(ll a, ll b) {
  if (a < b) swap(a, b);
  while (b) {
    ll t = a%b;
    a = b;
    b = t;
  }
  return a;
}

ll mem[1<<15][100];
ll dp(int s, int r) {
  ll &ret = mem[s][r];
  if (ret != -1) return ret;
  if (s == 0) {
    return ret = (r == 0);
  }
  ret = 0;
  for (int i = 0; i < n; i++) {
    if (s & (1<<i)) {
      int t = r * p10[len[i]] + arr[i];
      ret += dp(s^(1<<i), t%k);
    }
  }
  return ret;
}

int main() {
  cin >> n;
  for (int i = 0; i < n; i++) cin >> arr_s[i];
  cin >> k;

  p10[0] = 1;
  for (int i = 1; i < 1000; i++) p10[i] = (p10[i-1]*10)%k;

  for (int i = 0; i < n; i++) {
    char* ch = arr_s[i];
    for (; *ch != 0; ++ch) {
      arr[i] = (arr[i]*10 + *ch - '0') % k;
    }
    len[i] = ch - arr_s[i];
  }
  memset(mem, 0xff, sizeof(mem));

  ll a = dp((1<<n)-1, 0);
  if (a == 0) {
    cout << "0/1\n";
  } else {
    ll b = 1;
    for (int i = 1; i <= n; i++) b *= i;
    ll g = gcd(a, b);
    a /= g;
    b /= g;
    cout << a << '/' << b << '\n';
  }
}
