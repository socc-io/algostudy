#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

const int MAX_N = 500050;

typedef long long ll;

const ll LL_MAX = 1ll << 60;
const int L_MAX = 0x7fffffff;

template <class T>
struct RMQ
{
	static const int DEPTH = 20;
	static const int N = 1 << DEPTH;

	T val[2 * N];
	T TINF;

	RMQ(T TINF_) { TINF = TINF_; }

	void init()
	{
		for(int i = 0; i < 2 * N; i++) val[i] = TINF;
	}

	void init(T* iv, int sz)
	{
		for(int i = 0; i < sz; i++) val[i + N] = iv[i];
		for(int i = sz; i < N; i++) val[i + N] = TINF;

		for(int i = N-1; i >= 1; i--) val[i] = min(val[i*2], val[i*2+1]);
	}

	void init(vector<T> &iv)
	{
		int sz = iv.size();
		for(int i = 0; i < sz; i++) val[i + N] = iv[i];

		int L = N, R = N + sz;
		L >>= 1; R >>= 1;

		while(L < R) {
			for(int i = L; i < R; i++) val[i] = min(val[i*2], val[i*2+1]);
			L >>= 1; R >>= 1;
		}
	}

	void set_value(int p, T v)
	{
		p += N;
		val[p] = v;
		p >>= 1;

		while(p) {
			val[p] = min(val[p*2], val[p*2+1]);
			p >>= 1;
		}
	}

	T query(int L, int R)
	{
		T ret = TINF;
		L += N; R += N;
		while(L < R) {
			if(L & 1) ret = min(ret, val[L++]);
			if(R & 1) ret = min(ret, val[--R]);

			L >>= 1; R >>= 1;
		}
		return ret;
	}
};

RMQ<pair<int,int>> rmq(make_pair(L_MAX, L_MAX));

struct edge {
  int v;
  ll w;
  edge() {}
  edge(int v, ll w): v(v),w(w) {}
};

int n, q;
ll ans;
vector<edge> adj[MAX_N];
int par[MAX_N][20];
vector<int> el;
int lev[MAX_N];
ll dist[MAX_N];

RMQ<pair<int,int>> lca_tbl (make_pair(L_MAX, 0));
pair<int,int> lca_sub[2*MAX_N];

int x_num, y_num;
int xs[MAX_N];
int ys[MAX_N];
bool is_x[MAX_N];

int lca(int p, int q)
{
	if(lev[p] > lev[q]) swap(p, q);
	return lca_tbl.query(lev[p], lev[q] + 1).second;
}

void init_tree(int u, int p) {
  lev[u] = el.size();
  el.push_back(u);
  for (auto e: adj[u]) {
    int v = e.v; ll w = e.w;
    if (v == p) continue;
    par[v][0] = u;
    for (int i = 1; i < 20; i++) {
      par[v][i] = par[par[v][i-1]][i-1];
    }
    dist[v] = dist[u] + w;
    init_tree(v, u);
    el.push_back(u);
  }
}

vector<pair<int,int>> ord, ord2, ord3;

pair<ll, ll> dfs(int p, int q, int rt)
{
  // printf("%d, %d, %d\n", p, q, rt);
	if(p+1 == q) {
		ll dd = (rt == -1 ? 0 : (dist[ord[p].second] - dist[rt]));

		if(is_x[ord[p].second]) return make_pair(dd, LL_MAX);
		else return make_pair(LL_MAX, dd);
	}

	int bas = (int) rmq.query(p,q-1).second;

	pair<ll, ll> lf = dfs(p, bas+1, ord2[bas].second),
				   rg = dfs(bas+1, q, ord2[bas].second);
	ll dd = (rt == -1 ? 0 : (dist[ord2[bas].second] - dist[rt]));

	ans = min(ans, min(lf.first + rg.second, lf.second + rg.first));
	return make_pair(dd + min(lf.first, rg.first), dd + min(lf.second, rg.second));
}

ll query()
{
  ord.clear(); ord2.clear(); ord3.clear();  
  for (int i = 0; i < x_num; i++) {
    ord.push_back({lev[xs[i]], xs[i]});
    is_x[xs[i]] = true;
  }
  for (int i = 0; i < y_num; i++) {
    ord.push_back({lev[ys[i]], ys[i]});
    is_x[ys[i]] = false;
  }
  sort(ord.begin(), ord.end());
  for (int i = 1; i < ord.size(); i++) {
    int a = ord[i-1].second, b = ord[i].second;
    int ca = lca(a, b);
    ord2.push_back({lev[ca], ca});
    ord3.push_back({lev[ca], i-1});
  }
  rmq.init(ord3);
  ans = LL_MAX;
  dfs(0, ord.size(), -1);
  return ans;
}

int main(void)
{
  scanf("%d%d", &n, &q);
  for (int i = 1; i < n; i++) {
    int a, b;
    ll w;
    scanf("%d%d%lld", &a, &b, &w);
    ++a; ++b;
    adj[a].emplace_back(b, w);
    adj[b].emplace_back(a, w);
  }
  init_tree(1, 0);
  for(int i = 0; i < el.size(); i++) {
		lca_sub[i] = make_pair(lev[el[i]], el[i]);
	}
	lca_tbl.init(lca_sub, el.size());
  for (int i = 0; i < q; i++) {
    scanf("%d%d", &x_num, &y_num);
    for (int j = 0; j < x_num; j++) scanf("%d", &xs[j]), ++xs[j];
    for (int j = 0; j < y_num; j++) scanf("%d", &ys[j]), ++ys[j];
    printf("%lld\n", query());
  }
}
