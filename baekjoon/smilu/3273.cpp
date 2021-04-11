#include <bits/stdc++.h>
using namespace std;

int n, arr[100100], x;

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cin >> n;
  for (int i = 0; i < n; i++) cin >> arr[i];
  cin >> x;
  sort(arr, arr+n);
  
  int lt = 0, rt = n-1;
  int ans = 0, bin;
  for (; lt < n; lt++) {
    if (lt > 0 && arr[lt - 1] == arr[lt]) {
      ans += bin;
      continue;
    }

    while (rt > lt && arr[lt] + arr[rt] > x) --rt;
    bin = 0;
    while (rt > lt && arr[lt] + arr[rt] == x) {
      ++bin;
      --rt;
    }
    ans += bin;
    if (rt <= lt) break;
  }
  cout << ans;
}
