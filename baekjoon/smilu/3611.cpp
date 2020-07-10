// ref: https://users.ics.aalto.fi/gionis/goldberg-techreport.pdf
// http://noj.am/3611

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const double eps = 1.0e-20;

struct maxflow{
  using t_cap = double;
  struct edg{
    int pos;
    t_cap cap;
    int rev, idx;
  };

  int n;
	vector<vector<edg>> gph;
  vector<int> dis;
  vector<int> pnt;

  maxflow(int n): n(n), gph(n), dis(n), pnt(n) {}
  maxflow(const maxflow &mf): maxflow(mf.n) {
    for (int i = 0; i < n; i++) {
      copy(mf.gph[i].begin(), mf.gph[i].end(), back_inserter(gph[i]));
    }
  }
 
	void clear(){
		for(int i=0; i<n; i++){
			gph[i].clear();
		}
	}
 
	void add_edge(int s, int e, t_cap x){
		gph[s].push_back({e, x, (int)gph[e].size(), -1});
		gph[e].push_back({s, 0, (int)gph[s].size()-1, -1});
	}
 
	void add_edge(int s, int e, t_cap x, int idx){
		gph[s].push_back({e, x, (int)gph[e].size(), idx});
		gph[e].push_back({s, 0, (int)gph[s].size()-1, -1});
	}
 
	bool bfs(int src, int sink){
    fill(dis.begin(), dis.end(), 0);
    fill(pnt.begin(), pnt.end(), 0);
		queue<int> que;
		que.push(src);
		dis[src] = 1;
		while(!que.empty()){
			int x = que.front();
			que.pop();
			for(int i=0; i<gph[x].size(); i++){
				edg e = gph[x][i];
				if(e.cap > eps && !dis[e.pos]){
					dis[e.pos] = dis[x] + 1;
					que.push(e.pos);
				}
			}
		}
		return dis[sink] > 0;
	}
 
	t_cap dfs(int x, int sink, t_cap f){
		if(x == sink) return f;
		for(; pnt[x] < gph[x].size(); pnt[x]++){
			edg e = gph[x][pnt[x]];
			if(e.cap > eps && dis[e.pos] == dis[x] + 1){
				t_cap w = dfs(e.pos, sink, min(f, e.cap));
				if(w){
					gph[x][pnt[x]].cap -= w;
					gph[e.pos][e.rev].cap += w;
					return w;
				}
			}
		}
		return 0;
	}
 
	t_cap match(int src, int sink){
		t_cap ret = 0;
		while(bfs(src, sink)){
			t_cap r;
			while((r = dfs(src, sink, 2e9))) ret += r;
		}
		return ret;
	}

  bool alone(int index) const {
    for (const auto &e: gph[index]) {
      if (e.cap > eps) return false;
    }
    return true;
  }

  vector<int> adj(int src) const {
    vector<int> ret;
    vector<bool> visit(n);
    queue<int> q;
    q.push(src);
    visit[src] = true;
    while (!q.empty()) {
      int f = q.front(); q.pop();
      ret.push_back(f);
      for (const auto &e: gph[f]) {
        if (e.cap <= eps) continue;
        const int v = e.pos;
        if (visit[v]) continue;
        visit[v] = true;
        q.push(v);
      }
    }
    return ret;
  }
};

int n, m, src, snk;
int g = 3;
int d[111];

bool try_g(const double g, const maxflow &_mf) {
  maxflow mf(_mf);
  for (int i = 1; i <= n; i++) mf.add_edge(i, snk, m+g*2-d[i]);
  mf.match(src, snk);
  return mf.alone(src);
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cin >> n >> m;
  if (m == 0) {
    cout << "1\n1";
    return 0;
  }
  src = 0;
  snk = n+1;
  maxflow mf(n+2);
  for (int i = 0; i < m; i++) {
    int a, b; cin >> a >> b;
    mf.add_edge(a, b, 1);
    mf.add_edge(b, a, 1);
    d[a]++;
    d[b]++;
  }
  for (int i = 1; i <= n; i++) {
    mf.add_edge(src, i, m);
  }
  double l = 0, u = m;
  double ag = m;
  double thres = 1.0 / n / (n-1);
  while (u-l >= thres) {
    double g = (l+u)/2;
    if (try_g(g, mf)) {
      u = g;
    } else {
      l = g;
      ag = g;
    }
  }
  for (int i = 1; i <= n; i++) mf.add_edge(i, snk, m+ag*2-d[i]);
  mf.match(src, snk);
  vector<int> S = mf.adj(src);
  sort(S.begin(), S.end());
  cout << S.size() - 1 << '\n';
  for (int v: S) {
    if (v == src) continue;
    cout << v << '\n';
  }
}
