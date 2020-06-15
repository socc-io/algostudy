#include <bits/stdc++.h>
using namespace std;

const char* s_digits =
"###...#.###.###.#.#.###.###.###.###.###\n"
"#.#...#...#...#.#.#.#...#.....#.#.#.#.#\n"
"#.#...#.###.###.###.###.###...#.###.###\n"
"#.#...#.#.....#...#...#.#.#...#.#.#...#\n"
"###...#.###.###...#.###.###...#.###.###\n";

vector<int> possible_digits(
  const vector<string> &board,
  const int sy
) {
  bool check[10];
  memset(check, 0x00, sizeof(check));
  for (int x = 0; x < 5; x++) {
    for (int dy = 0; dy < 3; dy++) {
      const int y = sy + dy;
      const char v = board[x][y];
      if (v == '.') continue;
      for (int i = 0; i < 10; i++) {
        const char u = s_digits[x*40 + dy + i*4];
        if (u == '.') check[i] = true;
      }
    }
  }
  vector<int> ret;
  for (int i = 0; i < 10; i++) {
    if (false == check[i]) ret.push_back(i);
  }
  return ret;
}

double average(const vector<int> &vt) {
  double sum = 0.0;
  for (auto v: vt) sum += (double)v;
  return sum / vt.size();
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int n; cin >> n;
  vector<string> board(5);
  for (string &s: board) cin >> s;
  double ret = 0.0;
  double pw = 1.0;
  for (int i = n-1; i >= 0; i--) {
    const int sy = (i << 2);
    const vector<int> digits = possible_digits(board, sy);
    if (digits.empty()) { cout << "-1\n"; return 0; }
    // cout << "digits: "; for (int v: digits) cout << v << ' '; cout << '\n';
    const double avg = average(digits) * pw;
    ret += avg;
    pw *= 10.0;
  }
  cout << fixed << setprecision(6) << ret << '\n';
}
