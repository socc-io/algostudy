#include <bits/stdc++.h>
using namespace std;

int n;
int arr[1000010];

int main() {
  cin.tie(0); ios::sync_with_stdio(0);
  cin >> n;
  vector< pair< int, int > > s;
  memset(arr, 0xff, sizeof(arr));
  for (int i = 0; i < n; i++) {
    int cur; cin >> cur;
    while (!s.empty() && s.back().first < cur) {
      arr[s.back().second] = cur;
      s.pop_back();
    }
    s.push_back(make_pair(cur, i));
  }
  for (int i = 0; i < n; i++) cout << arr[i] << ' ';
}
