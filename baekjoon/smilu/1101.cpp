#include <bits/stdc++.h>
using namespace std;

int n, m;
int arr[50][50];
bool chk[50];
int skip;

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cin >> n >> m;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) cin >> arr[i][j];
  }
  for (int i = 0; i < n; i++) {
    int f = -1;
    for (int j = 0; j < m; j++) {
      if (arr[i][j]) {
        if (f == -1) f = j;
        else { f = -2; break; }
      }
    }
    if (f == -1) ++skip;
    else if (f != -2) {
      if (!chk[f]) {
        chk[f] = true;
        ++skip;
      }
    }
  }
  cout << max(0, n-1-skip) << '\n';
}
