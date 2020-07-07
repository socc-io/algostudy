#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  char s[10];
  cin.getline(s, 10);
  cout << (((s[0]-'0') + (s[4]-'0') == (s[8]-'0')) ? "YES" : "NO");
}
  