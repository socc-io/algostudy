#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 222;
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

int adj_map[52][52];

int index(char ch) {
	if ('a' <= ch && ch <= 'z') {
		return ch - 'a' + 26;
	}
	return ch - 'A';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	int n; cin >> n;
	for (int i = 0; i < n; i++) {
		char a, b; cin >> a >> b;
		int c; cin >> c;
		int p = index(a), q = index(b);
		adj_map[p][q] += c;
		adj_map[q][p] += c;
	}
	for (int i = 0; i < 52; i++) {
		for (int j = i+1; j < 52; j++) {
			if (adj_map[i][j] == 0) continue;
			mf.add_edge(i, j, adj_map[i][j]);
			mf.add_edge(j, i, adj_map[i][j]);
		}
	}
	cout << mf.match(0, 25) << '\n';
}
