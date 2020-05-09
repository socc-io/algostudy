#include <vector>
using namespace std;

#define MAX_N 100000

int dfn[MAX_N];
int low[MAX_N];
int par[MAX_N];
int vis[MAX_N];
vector<int> adj[MAX_N];
vector<int> bcc[MAX_N];
int piv, c_piv;


void dfs(int x, int p){
	dfn[x] = low[x] = ++piv;
	par[x] = p;
	for(int i=0; i<adj[x].size(); i++){
		int w = adj[x][i];
		if(w == p) continue;
		if(!dfn[w]){
			dfs(w, x);
			low[x] = min(low[x], low[w]);
		}
		else{
			low[x] = min(low[x], dfn[w]);
		}
	}
}

void color(int x, int c){
	if(c > 0) bcc[x].push_back(c);
	vis[x] = 1;
	for(int i=0; i<adj[x].size(); i++){
		int w = adj[x][i];
		if(vis[w]) continue;
		if(dfn[x] <= low[w]){
			bcc[x].push_back(++c_piv);
			color(w, c_piv);
		}
		else{
			color(w, c);
		}
	}
}