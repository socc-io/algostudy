#include <bits/stdc++.h>
using namespace std;

const int ord = 36;
const int cap = 55;

char convert(char ch) {
  if (0 <= ch && ch <= 9) return '0' + ch;
  return 'A' + (ch - 10);
}
struct bigint {
  char v[cap];
  int len() const {
    int ret = cap - 1;
    while (ret >= 0 && v[ret] == 0) --ret;
    return max(ret + 1, 1);
  }
  void fill(char iv = 0) {
    for (int i = 0; i < cap; i++) v[i] = iv;
  }
  void from_string(const string &str) {
    int n = str.size();
    for (int i = 0; i < n; i++) {
      char ch = str[n-1-i];
      if ('0' <= ch && ch <= '9') ch -= '0';
      else if ('A' <= ch & ch <= 'Z') ch -= 'A' - 10;
      v[i] = ch;
    }
    for (int i = n; i < cap; i++) v[i] = 0;
  }
  string to_string() const {
    string ret;
    int l = len();
    for (int i = l-1; i >= 0; i--) ret += convert(v[i]);
    return ret;
  }
  bigint operator+(const bigint &b) const {
    char carry = 0;
    bigint ret;
    for (int i = 0; i < cap; i++) {
      char sum = v[i] + b.v[i] + carry;
      ret.v[i] = sum % ord;
      carry = sum / ord;
    }
    return ret;
  }
  void operator+=(const bigint &b) {
    (*this) = (*this) + b;
  }
  bool operator<(const bigint &b) const {
    for (int i = cap-1; i >= 0; i--) {
           if (v[i] < b.v[i]) return false;
      else if (v[i] > b.v[i]) return true;
    }
    return false;
  }
  bigint(char iv = 0) { fill(iv); }
};

bigint vs[50];
bigint gains[ord];

bigint gain(const bigint &val, char ch) {
  bigint ret;
  int l = val.len();
  for (int i = 0; i < l; i++) {
    ret.v[i] = val.v[i] == ch ? (35 - ch) : 0;
  }
  return ret;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);

  int n; cin >> n;
  for (int i = 0; i < n; i++) {
    string s; cin >> s;
    vs[i].from_string(s);
    // cout << "vs[" << i << "]: " << vs[i].to_string() << '\n';
    for (int j = 0; j < ord; j++) {
      gains[j] += gain(vs[i], j);
    }
  }
  int k; cin >> k;
  sort(gains, gains + ord);
  bigint sum;
  for (int i = 0; i < n; i++) sum += vs[i];
  for (int i = 0; i < k; i++) sum += gains[i];
  cout << sum.to_string() << '\n';
}
