#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAX_N = 2020;

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
  int n, m; cin >> n >> m;
  for (int i = 0; i < n; i++) {
    mf.add_edge(1, 2+i, 2);
    int cnt; cin >> cnt;
    for (int j = 0; j < cnt; j++) {
      int wi; cin >> wi;
      mf.add_edge(2+i, 2+n+wi-1, 1);
    }
  }
  for (int i = 0; i < m; i++) {
    mf.add_edge(2+n+i, 2+n+m, 1);
  }
  cout << mf.match(1, 2+n+m) << '\n';
}
