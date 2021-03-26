#include <bits/stdc++.h>
using namespace std;

int mem[21][21][21];

int w(int a, int b, int c) {
  if (a <= 0 || b <= 0 || c <= 0) return 1;
  if (a > 20 || b > 20 || c > 20) return w(20, 20, 20);
  int & ret = mem[a][b][c];
  if (ret != 0x3f3f3f3f) return ret;
  if (a < b && b < c) ret = w(a, b, c-1) + w(a, b-1, c-1) - w(a, b-1, c);
  else ret = w(a-1, b, c) + w(a-1, b-1, c) + w(a-1, b, c-1) - w(a-1, b-1, c-1);
  return ret;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  memset(mem, 0x3F, sizeof(mem));
  while (1) {
    int a, b, c;
    cin >> a >> b >> c;
    if (a == -1 && b == -1 && c == -1) break;
    cout << "w(" << a << ", " << b << ", " << c << ") = " << w(a, b, c) << '\n';
  }
}
