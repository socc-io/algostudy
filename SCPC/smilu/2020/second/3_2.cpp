#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>
#include <cstring>
#include <cmath>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pl;

struct Seg {
  int _v[1<<20];
  int _begin, _end;
  int _update(int n, int s, int e, int x, int uv) {
    if (s == e) return _v[n] += uv;
    int m = (s+e)>>1, l = n<<1, r = l|1;
    if (x <= m) _update(l,s,m,x,uv);
    else        _update(r,m+1,e,x,uv);
    return _v[n] = _v[l] + _v[r];
  }
public:
  Seg(int begin, int end) {
    _begin = begin;
    _end = end;
  }
  int update(int x, int uv) {
    return _update(1, _begin, _end, x, uv);
  }
};

int n, k, q;
pl qs[1010];
ll ps[200020];
ll ls[200020];
ll cps[200020];
ll cls[200020];
ll arr[400400];
int arr_idx;

int get_index(ll v) {
  return lower_bound(arr, arr + arr_idx, v) - arr;
}

struct CountSeg: public Seg {
  int _at(int n, int s, int e, int x) {
    if (s == e) return s;
    int m = (s+e)>>1, l = n<<1, r = l|1;
    if (_v[l] < x) return _at(r,m+1,e,x-_v[l]);
    return _at(l,s,m,x);
  }
public:
  CountSeg(int max_value=400040): Seg(0,max_value) {}
  int insert(int x) {
    // cout << "insert: " << arr[x] << '\n';
    return update(x, 1);
  }
  int remove(int x) {
    // cout << "remove: " << arr[x] << '\n';
    return update(x, -1);
  }
  int at(int x) {
    return _at(1, _begin, _end, x+1);
  }
  int median() {
    const int l = _v[1];
    if (l & 1) return arr[at(l >> 1)];
    return arr[at(l>>1)];
  }
} seg;

bool flag = true;

void solve() {
  cin >> n >> k >> q;
  
  for (int i = 0; i < n; i++) scanf("%lld", &ps[i]);
  
  memset(ls, 0x00, sizeof(ls));
  ll sum = 0;
  arr_idx = 0;
  for (int i = 0; i < k-1; i++) sum += ps[i];
  for (int i = k-1; i < n; i++) {
    sum += ps[i];
    ls[i-k+1] = sum;
    arr[arr_idx++] = sum;
    sum -= ps[i-k+1];
  }
  memcpy(cps, ps, sizeof(ps));
  memcpy(cls, ls, sizeof(ls));
  for (int i = 0; i < q; i++) {
    scanf("%lld%lld", &qs[i].first, &qs[i].second);
    int a = qs[i].first - 1;
    const ll diff = qs[i].second - cps[a];
    const int i_begin = max(0, a-k+1);
    const int i_end   = min(n-k+1, a+1);
    for (int i = i_begin; i < i_end; i++) {
      cls[i] += diff;
      arr[arr_idx++] = cls[i];
    }
    cps[a] = qs[i].second;
  }
  sort(arr, arr + arr_idx);
  arr_idx = unique(arr, arr + arr_idx) - arr;

  // cout << "Arr: "; for (int i = 0; i < arr_idx; i++) cout << arr[i] << ' '; cout << '\n';

  memset(seg._v, 0x00, sizeof(seg._v));
  for (int i = 0; i < n-k+1; i++) {
    seg.insert(get_index(ls[i]));
  }
  cout << seg.median() << ' ';
  for (int i = 0; i < q; i++) {
    int a = qs[i].first - 1;
    const ll diff = qs[i].second - ps[a];
    const int i_begin = max(0, a-k+1);
    const int i_end   = min(n-k+1, a+1);
    for (int i = i_begin; i < i_end; i++) {
      seg.remove(get_index(ls[i]));
      ls[i] += diff;
      seg.insert(get_index(ls[i]));
      // cout << "ls: "; for (int i = 0; i < n-k+1; i++) cout << ls[i] << ' '; cout << '\n';
    }
    ps[a] = qs[i].second;
    cout << seg.median() << ' ';
  }
  cout << '\n';
}

int main(int argc, char** argv)
{
  setbuf(stdout, NULL);

	int T, test_case;

	cin >> T;
	for(test_case = 0; test_case  < T; test_case++)
	{
		cout << "Case #" << test_case+1 << endl;
		solve();
	}

	return 0;//Your program should return 0 on normal termination.
}