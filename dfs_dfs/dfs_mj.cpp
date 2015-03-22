#include <stdio.h>

int graph[11][11] = {0, };
int q,w;
int visit[11] = {0, };
void dfs(int a){
	int i;
	if(visit[a] != 1){
		visit[a] = 1;
		printf("%d ",a);
		for(i=1; i<=q;i++){
			if(graph[a][i] == 1){
				graph[a][i] = 0;
				graph[i][a] = 0;
				dfs(i);
			}
		}
	}
}
int main(){
	int m,n;
	scanf("%d %d",&q,&w);
	while(scanf("%d %d",&m,&n) != EOF){
		graph[m][n] = 1;
		graph[n][m] = 1;
	}
	dfs(w);
	return 0;
}