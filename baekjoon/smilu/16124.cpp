#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int SEG_SIZE = 1<<21;
const int MAX_N = 1000001;
const ll mod = 998244353;

char str[MAX_N];
int s_len;

ll pw10[MAX_N];

void init_pow10() {
  pw10[0] = 1;
  for (int i = 1; i < MAX_N; i++) {
    pw10[i] = (pw10[i-1] * 10) % mod;
  }
}

struct Seg {
  ll v[SEG_SIZE][10];
  ll lz[SEG_SIZE][10];
  void init(int n, int s, int e) {
    for (int i = 0; i < 10; i++) lz[n][i] = i;
    if (s == e) {
      v[n][str[s-1]-'0'] = 1;
    } else {
      int m = (s+e)>>1, l = n<<1, r = l|1;
      init(l,s,m); init(r,m+1,e);
      for (int i = 0; i < 10; i++) {
        v[n][i] = (pw10[e-m] * v[l][i] + v[r][i]) % mod;
      }
    }
  }
  bool clean(int n) {
    for (int i = 0; i < 10; i++) {
      if (lz[n][i] != i) return false;
    }
    return true;
  }
  void push(int n, int s, int e) {
    if (clean(n)) return;
    vector<ll> tmp(10, 0);
    
    for (int i = 0; i < 10; i++) tmp[lz[n][i]] = (tmp[lz[n][i]] + v[n][i]) % mod;
    for (int i = 0; i < 10; i++) v[n][i] = tmp[i];
    if (s != e) {
      int l = n<<1, r = l|1;
      for (int i = 0; i < 10; i++) tmp[i] = lz[n][lz[l][i]];
      for (int i = 0; i < 10; i++) lz[l][i] = tmp[i];
      for (int i = 0; i < 10; i++) tmp[i] = lz[n][lz[r][i]];
      for (int i = 0; i < 10; i++) lz[r][i] = tmp[i];
    }
    for (int i = 0; i < 10; i++) lz[n][i] = i;
  }
  void update(int n, int s, int e, int f, int t, int src, int dst) {
    push(n, s, e);
    if (t < s || e < f) return;
    if (f <= s && e <= t) {
      lz[n][src] = dst;
      push(n, s, e);
    } else {
      int m = (s+e)>>1, l = n<<1, r = l|1;
      update(l,s,m,f,t,src,dst);
      update(r,m+1,e,f,t,src,dst);
      for (int i = 0; i < 10; i++) {
        v[n][i] = (pw10[e-m] * v[l][i] + v[r][i]) % mod;
      }
    }
  }
  ll query(int n, int s, int e, int f, int t) {
    push(n, s, e);
    if (t < s || e < f) return 0;
    if (f <= s && e <= t) {
      ll ret = 0;
      for (int i = 0; i < 10; i++) ret = (ret + v[n][i] * i) % mod;
      return ret;
    }
    int m = (s+e)>>1, l = n<<1, r = l|1;
    if (m+1 <= t) {
      return (pw10[min(e, t) - m] * query(l,s,m,f,t) + query(r,m+1,e,f,t)) % mod;
    } else {
      return query(l,s,m,f,t);
    }
  }
} seg;

int main(void)
{
  init_pow10();
  scanf("%s", str);
  s_len = strlen(str);
  seg.init(1,1,s_len);
  int q; scanf("%d", &q);
  while (q--) {
    int op; scanf("%d", &op);
    if (op == 1) {
      int i, j, from, to;
      scanf("%d%d%d%d", &i, &j, &from, &to);
      seg.update(1,1,s_len,i,j,from,to);
    } else {
      int i, j; scanf("%d%d", &i, &j);
      printf("%lld\n", seg.query(1,1,s_len,i,j));
    }
  }
}
