#include <bits/stdc++.h>
using namespace std;

typedef pair<int,pair<int,int>> Item;

bool distinct(int a, int b, int c, int d) {
  if (a == b) return false;
  if (a == c) return false;
  if (a == d) return false;
  if (b == c) return false;
  if (b == d) return false;
  if (c == d) return false;
  return true;
}

int main(void)
{
  ios::sync_with_stdio(0); cin.tie(0);
  int w, n; cin >> w >> n;
  int m = n*(n-1)/2;
  vector<int> arr(n);
  vector<Item> items;
  items.reserve(m);
  for (int i = 0; i < n; i++) cin >> arr[i];
  for (int i = 0; i < n; i++) {
    for (int j = i+1; j < n; j++) {
      Item item = {arr[i] + arr[j], {i, j}};
      items.push_back(item);
    }
  }
  sort(items.begin(), items.end());
  bool flag = false;
  for (int i = 0; i < m; i++) {
    auto L = items[i];
    int R_first = w - L.first;
    Item lo_cmp = {R_first, {-1, -1}};
    auto lo = lower_bound(items.begin(), items.end(), lo_cmp);
    Item up_cmp = {R_first, {5050, 5050}};w
    auto up = upper_bound(items.begin(), items.end(), up_cmp);
    for (auto it = lo; it != up; it++) {
      if (distinct(L.second.first, L.second.second, it->second.first, it->second.second)) {
        flag = true;
        break;
      }
    }
    if (flag) break;
  }
  puts(flag ? "YES" : "NO");
}
