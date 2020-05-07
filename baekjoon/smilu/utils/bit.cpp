typedef long long ll;

#define MAX_N 1000000

struct bit_point_update_range_query {
  ll ft[MAX_N];
  void update(int x, ll v) {
    for (int i = x; i <= MAX_N; i+=(i&-i)) ft[i] += v;
  }
  ll query(int x) {
    ll ret = 0;
    for (int i = x; i > 0; i-=(i&-i)) ret += ft[i];
    return ret;
  }
  ll query(int a, int b) {
    return query(b) - query(a-1);
  }
};

struct bit_range_update_point_query {
  ll ft[MAX_N];
  void update(int x, ll v) {
    for (int i = x; i <= MAX_N; i+=(i&-i)) ft[i] += v;
  }
  void update(int a, int b, ll v) {
    update(a, v);
    update(b+1, -v);
  }
  ll query(int x) {
    ll ret = 0;
    for (int i = x; i > 0; i-=(i&-i)) ret += ft[i];
    return ret;
  }
};

struct bit_range_update_range_query {
  ll ft1[MAX_N], ft2[MAX_N];
  void update(int x, ll v, ll ft[]) {
    for (int i = x; i <= MAX_N; i+=(i&-i)) ft[i] += v;
  }
  void update(int a, int b, ll v) {
    update(a, v, ft1);
    update(b+1, -v, ft1);
    update(a, v*(a-1), ft2);
    update(b+1, -v * b, ft2);
  }
  ll query(int x, ll ft[]) {
    ll ret = 0;
    for (int i = x; i > 0; i-=(i&-i)) ret += ft[i];
    return ret;
  }
  ll query(int x) {
    return query(x, ft1) - x * query(x, ft2);
  }
  ll query(int a, int b) {
    return query(b) - query(a-1);
  }
};

