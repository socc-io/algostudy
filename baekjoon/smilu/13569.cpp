#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 500;
struct maxflow{
	struct edg{int pos, cap, rev, idx;};
	vector<edg> gph[MAXN];
 
	void clear(){
		for(int i=0; i<MAXN; i++){
			gph[i].clear();
		}
	}
 
	void add_edge(int s, int e, int x){
		gph[s].push_back({e, x, (int)gph[e].size(), -1});
		gph[e].push_back({s, 0, (int)gph[s].size()-1, -1});
	}
 
	void add_edge(int s, int e, int x, int idx){
		gph[s].push_back({e, x, (int)gph[e].size(), idx});
		gph[e].push_back({s, 0, (int)gph[s].size()-1, -1});
	}
 
	int dis[MAXN], pnt[MAXN];
 
	bool bfs(int src, int sink){
		memset(dis, 0, sizeof(dis));
		memset(pnt, 0, sizeof(pnt));
		queue<int> que;
		que.push(src);
		dis[src] = 1;
		while(!que.empty()){
			int x = que.front();
			que.pop();
			for(int i=0; i<gph[x].size(); i++){
				edg e = gph[x][i];
				if(e.cap > 0 && !dis[e.pos]){
					dis[e.pos] = dis[x] + 1;
					que.push(e.pos);
				}
			}
		}
		return dis[sink] > 0;
	}
 
	int dfs(int x, int sink, int f){
		if(x == sink) return f;
		for(; pnt[x] < gph[x].size(); pnt[x]++){
			edg e = gph[x][pnt[x]];
			if(e.cap > 0 && dis[e.pos] == dis[x] + 1){
				int w = dfs(e.pos, sink, min(f, e.cap));
				if(w){
					gph[x][pnt[x]].cap -= w;
					gph[e.pos][e.rev].cap += w;
					return w;
				}
			}
		}
		return 0;
	}
 
	ll match(int src, int sink){
		ll ret = 0;
		while(bfs(src, sink)){
			int r;
			while((r = dfs(src, sink, 2e9))) ret += r;
		}
		return ret;
	}
} mf;

int ret[50000];

void add_lr_edge(int u, int v, double f, int idx = -1) {
  int l = (int)floor(f);
  int r = (int)ceil(f);
  if (idx != -1) ret[idx] += r;
  mf.add_edge(u, v, r-l, idx);
  mf.add_edge(1, v, l);
  mf.add_edge(u, 2, l);
}

int main(void)
{
  double tmp;
  int n, m; scanf("%d%d", &n, &m);
  int piv = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      scanf("%lf", &tmp);
      add_lr_edge(5+i, 5+n+j, tmp, piv++);
    }
    scanf("%lf", &tmp);
    add_lr_edge(3, 5+i, tmp, piv++);
  }
  for (int i = 0; i < m; i++) {
    scanf("%lf", &tmp);
    add_lr_edge(5+n+i, 4, tmp, piv++);
  }
  mf.add_edge(4, 3, 0x3f3f3f3f);

  mf.match(1, 2);

  for (int i = 1; i <= n+m+4; i++) {
    for (const auto &e: mf.gph[i]) {
      if (e.idx == -1) continue;
      ret[e.idx] -= e.cap;
    }
  }

  piv = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      printf("%d ", ret[piv++]);
    }
    printf("%d ", ret[piv++]);
    puts("");
  }
  for (int i = 0; i < m; i++) {
    printf("%d ", ret[piv++]);
  } puts("");
}
