#include <bits/stdc++.h>
using namespace std;

enum {
  BRACKET_OPEN = 1,
  BRACKET_CLOSE = 2,
};

inline int BranchBracket(char ch) {
  if (ch == '[' || ch == '(') return BRACKET_OPEN;
  if (ch == ']' || ch == ')') return BRACKET_CLOSE;
  return 0;
}

inline char Opposite(char ch) {
  return ch == ')' ? '(' : '[';
}

bool ProcessLine(const string & line) {
  vector<char> s;

  for (auto it = line.begin(); it != line.end(); it++) {
    char ch = (*it);
    switch (BranchBracket(ch)) {
      case BRACKET_OPEN:
        s.push_back(ch);
        break;
      case BRACKET_CLOSE:
        if (s.empty() || s.back() != Opposite(ch)) return false;
        s.pop_back();
        break;
    }
  }

  return s.empty();
}

int main() {
  cin.tie(0); ios::sync_with_stdio(0);
  string line;
  while (getline(cin, line)) {
    if (line == ".") break;
    cout << (ProcessLine(line) ? "yes" : "no") << '\n';
  }
}
