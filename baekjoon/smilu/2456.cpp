#include <bits/stdc++.h>
using namespace std;

typedef tuple<int,int,int,int> det;

void add(det &d) {
  int t; cin >> t;
  if (t == 3) {
    get<0>(d) += 3;
    get<1>(d)++;
  } else if (t == 2) {
    get<0>(d) += 2;
    get<2>(d)++;
  } else if (t == 1) {
    get<0>(d) += 1;
    get<3>(d)++;
  }
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  vector<det> ds = {{0,0,0,0},{0,0,0,0},{0,0,0,0}};
  int n; cin >> n;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < 3; j++) {
      add(ds[j]);
    }
  }
  const int mi = (max_element(ds.begin(), ds.end()) - ds.begin());
  for (int i = 0; i < 3; i++) if (i != mi && ds[i] == ds[mi]) {
    cout << "0 " << get<0>(ds[mi]);
    return 0;
  }
  cout << mi+1 << ' ' << get<0>(ds[mi]);
}
