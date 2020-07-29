#include <bits/stdc++.h>
using namespace std;

char names[20][61];
char tile[20][20];

void solve(const int n) {
  for (int i = 0; i < n; i++) {
    cin >> names[i];
    for (int j = 0; j < n-1; j++) {
      cin >> tile[i][j]; 
    }
  }
  bool flag = false;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n-1; j++) {
      const char ch = tile[i][j];
      if (ch == 'N') {
        cout << names[(i-j-1+n)%n] << " was nasty about " << names[i] << '\n';
        flag = true;
      }
    }
  }
  if (!flag) {
    cout << "Nobody was nasty\n";
  }
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int index = 1;
  while (1) {
    int n; cin >> n;
    if (n == 0) break;
    cout << "Group " << (index++) << '\n';
    solve(n);
    cout << '\n';
  }
}
