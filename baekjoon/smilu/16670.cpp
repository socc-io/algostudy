#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;

struct Seg {
  ll ed[4000000];
  ll ct[4000000];
  void push(int n, int l, int r) {
    ct[n] = ct[l] + ct[r];
    ed[n] = max(ed[r], ed[l] + ct[r]);
  }
  void init(int n, int s, int e) {
    if (s == e) {
      ed[n] = s;
      ct[n] = 0;
    } else {
      int m = (s+e)>>1, l = n<<1, r = l|1;
      init(l,s,m);
      init(r,m+1,e);
      push(n,l,r);
    }
  }
  void update(int n, int s, int e, int x, ll val) {
    if (s == e) {
      ed[n] += val;
      ct[n] += val;
    } else {
      int m = (s+e)>>1, l = n<<1, r = l|1;
      if (x <= m) update(l,s,m,x,val);
      else        update(r,m+1,e,x,val);
      push(n,l,r);
    }
  }
  void update(int x, ll val) {
    update(1,1,1000000,x,val);
  }
  ll ans;
  void query(int n, int s, int e, int x) {
    if (e <= x) ans = max(ans + ct[n], ed[n]);
    else {
      int m = (s+e)>>1, l = n<<1, r = l|1;
      query(l,s,m,x);
      if (m < x) query(r,m+1,e,x);
    }
  }
  ll query(int x) {
    ans = 0;
    query(1,1,1000000,x);
    return ans;
  }
} seg;

int main(void) {
  int q; scanf("%d", &q);
  vector<pair<int,int>> qs(300001);
  seg.init(1,1,1000000);
  for (int i = 1; i <= q; i++) {
    char cmd[2];
    scanf("%s", cmd);
    if (cmd[0] == '?') {
      ll x; scanf("%lld", &x);
      printf("%lld\n", max(seg.query(x)-x, 0LL));
    } else if (cmd[0] == '+') {
      int a, b; scanf("%d%d", &a, &b);
      qs[i] = {a, b};
      seg.update(a, b);
    } else { // '-'
      int x; scanf("%d", &x);
      seg.update(qs[x].first, -qs[x].second);
    }
  }
}

