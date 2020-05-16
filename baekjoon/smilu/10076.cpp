#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAX_N = 101010;
const int MAX_SEG = MAX_N*4;

struct Seg {
  ll  sum[MAX_SEG];
  int cnt[MAX_SEG];
  void clear() {
    memset(sum, 0x00, sizeof(sum));
    memset(cnt, 0x00, sizeof(cnt));
  }
  void update(int n, int s, int e, int x, ll val) {
    if (x < s || x > e) return;
    if (s == e) {
      if (val >= 0) {
        sum[n] = val;
        cnt[n] = 1;
      } else {
        sum[n] = cnt[n] = 0;
      }
    } else {
      int m = (s + e) >> 1, l = n << 1, r = l | 1;
      if (x <= m) update(l, s, m, x, val);
      else update(r, m+1, e, x, val);
      sum[n] = sum[l] + sum[r];
      cnt[n] = cnt[l] + cnt[r];
    }
  }
  void update(int x, ll val) {
    update(1, 0, MAX_N-1, x, val);
  }
  pair<ll, int> query_top(int n, int s, int e, int num) const {
    if (num <= 0) return {0, 0};
    if (cnt[n] <= num) return {sum[n], cnt[n]};
    int m = (s + e) >> 1, l = n << 1, r = l | 1;
    auto R = query_top(r, m+1, e, num);
    auto L = query_top(l, s, m, num - R.second);
    return {L.first + R.first, L.second + R.second};
  }
  ll query_top(int num) const {
    return query_top(1, 0, MAX_N-1, num).first;
  }
  Seg() { clear(); }
} seg;

template <class T>
vector<int> build_ranks(const vector<T> &arr) {
  vector<pair<T, int>> items(arr.size());
  for (int i = 0; i < arr.size(); i++) {
    items[i] = {arr[i], i};
  }
  sort(items.begin(), items.end());
  vector<int> ret(arr.size());
  for (int i = 0; i < arr.size(); i++) {
    const auto &I = items[i];
    ret[I.second] = i;
  }
  return ret;
}

void dnc(
  const vector<ll> &points,
  const vector<int> &ranks,
  vector<ll> &res,
  vector<int> &pos,
  int s, int e, int l, int r
) {
  if (s > e) return;
  int m = (s + e) >> 1;
  ll max_val = -1;
  int max_index = -1;
  for (int i = l; i <= min(m, r); i++) {
    seg.update(ranks[i], points[i]);
    ll sum = seg.query_top(m - i);
    if (sum > max_val) {
      max_val = sum;
      max_index = i;
    }
  }
  res[m] = max_val;
  pos[m] = max_index;
  if (s == e) return;
  for (int i = l; i <= r; i++) seg.update(ranks[i], -1);
  dnc(points, ranks, res, pos, s, m-1, l, max_index);
  for (int i = l; i < max_index; i++) seg.update(ranks[i], points[i]);
  dnc(points, ranks, res, pos, m+1, e, max_index, r);
}

pair<vector<ll>,vector<int>> get_optimized(const vector<ll> &points) {
  vector<int> point_ranks = build_ranks(points);

  seg.clear();
  int n = points.size();
  int max_time = 2*n - 1;
  vector<ll>  max_att(max_time+1);
  vector<int> pos(max_time+1);
  dnc(points, point_ranks, max_att, pos, 0, max_time, 0, n-1);

  // printf("max: "); for (auto t: max_att) printf("%lld ", t); puts("");
  // printf("pos: "); for (auto t: pos) printf("%d ", t); puts("");

  return {max_att, pos};
}

ll solve(int n, int start, int d, ll ps[])
{
  vector<ll> right(n - start + 1);
  for (int i = start; i <= n; i++) {
    right[i - start] = ps[i];
  }
  auto R = get_optimized(right);
  const auto &R_max = R.first;
  const auto &R_pos = R.second;

  ll ret = R_max[min((int)R_max.size() - 1, d)];

  if (start <= 1) return ret;

  vector<ll> left(start - 1);
  for (int i = start - 1; i >= 1; i--) {
    left[start - 1 - i] = ps[i];
  }
  auto L = get_optimized(left);
  const auto &L_max = L.first;

  for (int rt = 0; rt < R_max.size(); rt++) {
    ll sub = R_max[rt];
    int lt = d - rt - R_pos[rt] - 1;
    if (lt < 0) break;
    sub += L_max[min((int)L_max.size() - 1, lt)];
    ret = max(ret, sub);
  }

  return ret;
}

int n, start, d;
ll ps[MAX_N];

int main()
{
  scanf("%d%d%d", &n, &start, &d);
  for (int i = 1; i <= n; i++) scanf("%lld", &ps[i]);
  ++start;
  ll origin = solve(n, start, d, ps);
  reverse(ps + 1, ps + n + 1);
  ll reversed = solve(n, n - start + 1, d, ps);
  printf("%lld\n", max(origin, reversed));
}
