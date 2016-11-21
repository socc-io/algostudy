#include <iostream>
using namespace std;

int N,M,s,t;
int map[403][403];

void init(){
  for(int i = 0; i < N+M ; i++){
    for(int j = 0; j < N+M ; j++){
      map[i][j] = 0;
    }
  }
}

int dfs(int now, int min_val){
  cout << now << endl;
  if (now == t){
    return min_val;
  }else{
    for (int i = 0; i < 403 ; i++){
      if (map[now][i] > 0){
        int n_val = (map[now][i] < min_val)? map[now][i] : min_val;
        int res = dfs(i, n_val);
        if(res > 0){
          min_val = (res < min_val)? res : min_val;
          map[now][i] -= min_val;
          map[i][now] += min_val;
          return min_val;
        }
      }
    }
    return 0;
  }
}

int main(void){
  cin >> N >> M;
  s = 0; t = N + M + 1;
  init();
  for(int i = 1; i <= N ; i++){
    int si;
    cin >> si;
    map[0][i] = 9999;
    for (int j = 0; j < si ; j++){
      int wannago;
      cin >> wannago;
      wannago += N;
      map[i][wannago] = 1;
      map[wannago][t] = 9999;
    }
    int max_flow = 0;
    while(true){
      int res = dfs(0, 9999);
      if (res > 0) {
        max_flow += res;
      }else{
        break;
      }
    }
    cout << max_flow << endl;
  }
  return 0;
}

