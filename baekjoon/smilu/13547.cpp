#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;

struct Query {
  int index;
  int l, r;
  int ans;
};

int mo_size;
bool mo_sort(const Query &a, const Query &b) {
  int p = a.r / mo_size;
  int q = b.r / mo_size;
  return p == q ? a.l < b.l : p < q;
}
bool index_sort(const Query &a, const Query &b) {
  return a.index < b.index;
}

int n, c, m;
int as[100010];
Query ps[100010];

int cnt[1000001];
int s_cnt;
void inc(int x) {
  s_cnt += cnt[x] == 0;
  ++cnt[x];
}
void dec(int x) {
  s_cnt -= cnt[x] == 1;
  --cnt[x];
}

int main(void)
{
  ios::sync_with_stdio(0); cin.tie(0);
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> as[i];
  cin >> m;
  for (int i = 0; i < m; i++) {
    ps[i].index = i;
    cin >> ps[i].l >> ps[i].r;
  }
  
  mo_size = sqrt(n);
  sort(ps, ps + m, mo_sort);
  
  int l = ps[0].l, r = ps[0].l - 1;
  for (int i = 0; i < m; i++) {
    int nl = ps[i].l;
    int nr = ps[i].r;
    while (l < nl) dec(as[l++]);
    while (l > nl) inc(as[--l]);
    while (r < nr) inc(as[++r]);
    while (r > nr) dec(as[r--]);
    ps[i].ans = s_cnt;
  }
  sort(ps, ps + m, index_sort);
  for (int i = 0; i < m; i++) {
    cout << ps[i].ans << '\n';
  }
}
