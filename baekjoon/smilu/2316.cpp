#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAX_N = 1200;

struct maxflow{
	struct edg{int pos, cap, rev, idx;};
	vector<edg> gph[MAX_N];
 
	void clear(){
		for(int i=0; i<MAX_N; i++){
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
 
	int dis[MAX_N], pnt[MAX_N];
 
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

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int n, p; cin >> n >> p;
  for (int i = 1; i <= n; i++) {
    mf.add_edge(i*2-1, i*2, 1);
  }
  for (int i = 0; i < p; i++) {
    int a, b; cin >> a >> b;
    const int ao = (a<<1);
    const int ai = ao - 1;
    const int bo = (b<<1);
    const int bi = bo - 1;
    mf.add_edge(ao, bi, 1);
    mf.add_edge(bo, ai, 1);
  }
  cout << mf.match(2, 3) << '\n';
}
