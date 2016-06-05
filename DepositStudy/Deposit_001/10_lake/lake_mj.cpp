#include <stdio.h>
char arr[102][102] = {0, };

int DFS(int a,int b){
	if(arr[a-1][b] == 'W'){
		arr[a-1][b] = '.';
		DFS(a-1,b);
	}
	if(arr[a-1][b] == 'W'){
		arr[a-1][b] = '.';
		DFS(a-1,b);
	}
	if(arr[a+1][b] == 'W'){
		arr[a+1][b] = '.';
		DFS(a+1,b);
	}
	if(arr[a][b+1] == 'W'){
		arr[a][b+1] = '.';
		DFS(a,b+1);
	}
	if(arr[a][b-1] == 'W'){
		arr[a][b-1] = '.';
		DFS(a,b-1);
	}
	if(arr[a+1][b+1] == 'W'){
		arr[a+1][b+1] = '.';
		DFS(a+1,b+1);
	}
	if(arr[a-1][b+1] == 'W'){
		arr[a-1][b+1] = '.';
		DFS(a-1,b+1);
	}
	if(arr[a-1][b-1] == 'W'){
		arr[a-1][b-1] = '.';
		DFS(a-1,b-1);
	}
	if(arr[a+1][b-1] == 'W'){
		arr[a+1][b-1]= '.';
		DFS(a+1,b-1);
	}
	return 0;
}
int main(){
	int M,N;
	int answer = 0;
	scanf("%d %d",&M,&N);
	for(int i=1;i<=M;i++){
		for(int j=1;j<=N;j++){
			scanf(" %c",&arr[i][j]);
		}
	}
	for(int i=1;i<=M;i++){
		for(int j=1;j<=N;j++){
			if(arr[i][j] == 'W'){
				DFS(i,j);
				answer++;
			}
		}
	}
	printf("%d\n",answer);
	return 0;
}