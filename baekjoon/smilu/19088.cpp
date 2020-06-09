#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll mod = 1000000007;

int n, q, d;
ll cards[100010];
pair<int, ll> queries[100010];
ll pw[1000100];
ll pws[1000100];

class Zipper: public vector<ll> {
public:
  void add(ll v) {
    push_back(v);
  }
  void organize() {
    sort(begin(), end());
    erase(unique(begin(), end()), end());
  }
  int get(ll v) {
    return distance(begin(), lower_bound(begin(), end(), v));
  }
};

struct Int {
  ll val;
  int len;
  Int concat(const Int &b) const {
    Int ret;
    ll tmp = (val * pw[b.len]) % mod;
    tmp += b.val;
    tmp %= mod;
    ret.val = tmp;
    ret.len = len + b.len;
    return ret;
  }
  Int() {}
  Int(ll v, int cnt) {
    val = (pws[cnt]*v) % mod;
    len = cnt;
  }
};

struct Seg {
  Int v[1<<19];
  void update(int n, int s, int e, int x, Int val) {
    if (s == e) {
      v[n] = val;
      return;
    }
    int m = (s+e)>>1, l = n<<1, r = l|1;
    if (x <= m) update(l,s,m,x,val);
    else update(r,m+1,e,x,val);
    v[n] = v[r].concat(v[l]);
  }
  Int query(int n, int s, int e, int x) {
    if (s == e) return v[n];
    int m = (s+e)>>1, l = n<<1, r = l|1;
    if (x <= m) return query(l,s,m,x);
    return query(r,m+1,e,x);
  }
} seg;

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cin >> n >> q >> d;

  pw[0] = 1;
  pws[0] = 0;
  for (int i = 1; i < 1000100; i++) {
    pw[i] = (pw[i-1] * d) % mod;
    pws[i] = (pws[i-1] + pw[i-1]) % mod;
  }
  
  Zipper zip;

  for (int i = 0; i < n; i++) cin >> cards[i];
  for (int i = 0; i < n; i++) zip.add(cards[i]);
  for (int i = 0; i < q; i++) {
    auto &qr = queries[i];
    cin >> qr.first >> qr.second;
    --qr.first;
    zip.add(qr.second);
  }
  zip.organize();
  
  int k = zip.size();
  vector<int> cnt(k);
  for (int i = 0; i < n; i++) {
    cnt[zip.get(cards[i])]++;
  }
  for (int i = 0; i < k; i++) {
    seg.update(1,0,k-1,i,Int(zip[i], cnt[i]));
  }
  cout << seg.v[1].val << '\n';
  for (int i = 0; i < q; i++) {
    const auto &qr = queries[i];
    ll origin = cards[qr.first];
    int o_idx = zip.get(origin);
    cnt[o_idx]--;
    ll rep = qr.second;
    int r_idx = zip.get(rep);
    cnt[r_idx]++;
    cards[qr.first] = qr.second;

    Int o_val(origin, cnt[o_idx]);
    Int r_val(rep, cnt[r_idx]);
    seg.update(1,0,k-1,o_idx,o_val);
    seg.update(1,0,k-1,r_idx,r_val);
    cout << seg.v[1].val << '\n';

    // cout << "Seg:\n";
    // for (int j = 0; j < k; j++) {
    //   cout << "  " << zip[j] << ": " <<  seg.query(1,0,k-1,j).val << '\n';
    // }
  }
}
