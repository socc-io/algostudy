#include <bits/stdc++.h>
using namespace std;

void merge_sort(vector<int> &arr) {
  const int n = arr.size();
  vector<int> buf(n);
  for (int b_size = 2; (b_size>>1) < n; b_size <<= 1) {
    for (int i = 0; i < n; i += b_size) {
      const int hs = b_size >> 1;
      const int j = i + hs, k = min(n, i + b_size);
      if (j >= n) break;
      int bs = 0, ls = i, rs = j;
      while (ls < j && rs < k) buf[bs++] = arr[ls] < arr[rs] ? arr[ls++] : arr[rs++];
      while (ls < j) buf[bs++] = arr[ls++];
      while (rs < k) buf[bs++] = arr[rs++];
      copy(buf.begin(), buf.begin() + (k-i), arr.begin() + i);
    }
  }
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int n; cin >> n;
  vector<int> arr(n);
  for (int &v: arr) cin >> v;
  // for (int v: arr) cout << v << ' '; cout << '\n';
  merge_sort(arr);
  for (int v: arr) cout << v << '\n';
}
