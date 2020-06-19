#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int b_size = 16;
const ll base = 10000000000000000;

ll pwm[20];
ll pw(int i) {
  if (pwm[0]) return pwm[i];
  pwm[0] = 1;
  for (int i = 1; i < 20; i++) {
    pwm[i] = pwm[i-1] * 10;
  }
  return pwm[i];
}

class BigInt {
  int size;
  ll *vs;
public:
  void clear() {
    memset(vs, 0x00, sizeof(ll)*size);
  }
  void free() { delete[] vs; }
  void copy(const BigInt &b) {
    memcpy(vs, b.vs, sizeof(ll)*size);
  }
  string to_string() const {
    const int s_size = size * b_size;
    string ret;
    bool z_flag = false;
    for (int i = 0; i < s_size; i++) {
      const int ri = s_size-1-i;
      const int ui = ri / b_size;
      const int ur = ri - ui * b_size;
      const int cv = (vs[ui] / pw(ur)) % 10;
      if (cv) z_flag = true;
      if (z_flag) ret.push_back('0' + cv);
    }
    return ret;
  }
  BigInt(ll *vs, int size): size(size), vs(vs) {}
  BigInt(int size): size(size) {
    vs = new ll[size];
    clear();
  }
  BigInt(const string &s) {
    const int m_size = (s.size() + b_size - 1) / b_size;
    size = 1;
    while (size < m_size) size <<= 1;
    vs = new ll[size];
    clear();
    for (int i = 0; i < s.size(); i++) {
      const ll  cv = s[i] - '0';
      const int ri = s.size()-1-i;
      const int ui = ri / b_size;
      const int ur = ri - ui * b_size;
      vs[ui] += cv * pw(ur);
    }
  }
  void add(const BigInt &b, int off) {
    for (int i = 0; i < b.size; i++) vs[off+i] += b.vs[i];
  }
  void operator+=(const BigInt &b) {
    for (int i = 0; i < b.size; i++) vs[i] += b.vs[i];
  }
  BigInt operator+(const BigInt &b) const {
    assert(size == b.size);
    BigInt ret(size);
    ret.copy(*this);
    ret += b;
    return ret;
  }
  void operator-=(const BigInt &b) const {
    for (int i = 0; i < b.size; i++) vs[i] -= b.vs[i];
  }
  BigInt operator*(const BigInt &b) const {
    assert(size == b.size);

    if (size == 1) {
      BigInt ret(2);
      ll tmp = vs[0] * b.vs[0];
      ret.vs[0] = tmp % base;
      ret.vs[1] = tmp / base;
      return ret;
    }

    const int h_size = (size >> 1);
    const int d_size = (size << 1);

    // cout << "a: " << to_string() << '\n';
    // cout << "b: " << b.to_string() << '\n';

    const BigInt a0 = BigInt(vs + h_size, h_size);
    const BigInt a1 = BigInt(vs, h_size);
    const BigInt b0 = BigInt(b.vs + h_size, h_size);
    const BigInt b1 = BigInt(b.vs, h_size);
    BigInt z2 = a0 * b0;
    BigInt z0 = a1 * b1;
    BigInt a0a1 = a0 + a1;
    BigInt b0b1 = b0 + b1;
    BigInt z1 = a0a1 * b0b1;
    z1 -= z0;
    z1 -= z2;

    BigInt ret(d_size);
    memcpy(ret.vs + size, z2.vs, sizeof(ll)*size);
    memcpy(ret.vs, z0.vs, sizeof(ll)*size);
    ret.add(z1, h_size);

    z2.free();
    z0.free();
    a0a1.free();
    b0b1.free();
    z1.free();

    return ret;
  }
};

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  string s1, s2; cin >> s1 >> s2;
  BigInt a(s1), b(s2);

  BigInt ret = a*b;
  string rs = ret.to_string();
  cout << rs << '\n';

  cout << (BigInt(1<<17)*BigInt(1<<17)).to_string() << '\n';
}
