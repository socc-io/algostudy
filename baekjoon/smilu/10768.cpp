#include <bits/stdc++.h>
using namespace std;

const pair<int,int> _sd = {2, 18};

const char* solve(pair<int,int> d) {
  if (d < _sd) return "Before";
  if (d > _sd) return "After";
  return "Special";
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  pair<int, int> d; cin >> d.first >> d.second;
  cout << solve(d);
}
