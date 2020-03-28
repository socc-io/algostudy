#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool is_correct(string p) {
  int h = 0;
  for (int i = 0; i < p.size(); i++) {
    if (p[i] == '(') ++h;
    else {
      if (h > 0) h--;
      else return false;
    }
  }
  return h == 0;
}

string invert(string p) {
  string res(p);
  for (int i = 0; i < p.size(); i++) {
    res[i] = 81 - p[i];
  }
  return res;
}

string find_u(string p) {
  if (p.size() == 0) return "";
  int cnt[2] = {0, 0};
  int len = -1;
  cnt[p[0]-'(']++;
  for (int i = 1; i < p.size(); i++) {
    cnt[p[i]-'(']++;
    if (cnt[0] == cnt[1]) {
      len = i + 1;
      break;
    }
  }
  if (len == -1) return "";
  return p.substr(0, len);
}

string solution(string p) {
  if (p.size() == 0) return "";
  string u = find_u(p);
  string v = p.substr(u.size());
  if (is_correct(u)) return u + solution(v);
  return "(" + solution(v) + ")" + invert(u.substr(1, u.size() - 2));
}

int main(void)
{
  cout << solution(")(") << '\n';
}
