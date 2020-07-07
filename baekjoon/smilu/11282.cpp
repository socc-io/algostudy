#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int n; cin >> n;
  n += 0x6abff;
  cout 
    << (char)((n >> 12) | 0x80)
    << (char)(((n >> 6) & 0x3f) | 0x80)
    << (char)((n & 0x3f) | 0x80);
}
