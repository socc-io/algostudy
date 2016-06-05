#include <iostream>

using namespace std;

char map[101][101] = {0};
int dx[8] = {1,-1,0,0,1,1,-1,-1};
int dy[8] = {0,0,1,-1,1,-1,-1,1};
int N,M;

bool valid(int r, int c){ 
    return (r < 0 || r >= N || c < 0 || c >= M)? false : true;  
}

void dfs_w(int r, int c){ 
    map[r][c] = '.';
    for(int i = 0 ; i < 8 ; i++){
        int nr = r+dx[i];
        int nc = c+dy[i];
        if(valid(nr,nc) && map[nr][nc] == 'W')
            dfs_w(nr,nc);
    }   
}

int main(void){
    cin >> N >> M;
    for(int i = 0 ; i < N ;i ++){
        cin >> map[i];
    }   
    int count = 0;

    for(int i = 0 ; i < N ; i ++){
        for(int j = 0; j < M ; j++){
            if(map[i][j] == 'W'){
                dfs_w(i,j);
                count++;
            }   
        }    
    }   
    cout << count << endl;
    return 0;
}
