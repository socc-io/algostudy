#include <iostream>

using namespace std;

int T[1000001] = {0,};

int next_lower_idx(int i){
  i = i - (i & -i);
  return i;
}

int next_higher_idx(int i){
  i = i + (i & -i);
  return i;
}


int main(void){
  int N, M, K;
  cin >> N >> M >> K;
  for (int i = 1; i <= N ; i++){
    int now_idx = i;
    int value;
    cin >> value;
    while(now_idx <= N){
      T[now_idx] += value;
      now_idx = next_higher_idx(now_idx);
    }
  }
  for (int i = 0; i < K+M ; i++){
    int a,b,c,now_idx;
    cin >> a >> b >> c;
    if (a == 1){
      now_idx = b;
      int diff = c - T[now_idx];
      while(now_idx <= N){
        T[now_idx] += diff;
        now_idx = next_higher_idx(now_idx);        
      }
    }else{
      int bval = 0;
      now_idx = b - 1;
      while(now_idx > 0){
        bval += T[now_idx];
        now_idx = next_lower_idx(now_idx);        
      }
      int cval = 0;
      now_idx = c;
      while(now_idx > 0){
        cval += T[now_idx];
        now_idx = next_lower_idx(now_idx);        
      }
      cout << cval - bval << endl;
    }
  }

  return 0;
}
