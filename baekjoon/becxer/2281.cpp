#include <iostream>

using namespace std;
int seq[1001];
int dp[1001][1001]; // start , end
int main(void){
  int N,M;
  cin >> N >> M;
  for(int i = 0 ; i < N ; i++){
    cin >> seq[i];OA
  }
  for(int i = 0 ; i < N ; i++){ // i is end
    now_length = 0;
    now_start = i;
    while(now_length < M){
      dp[now_start][i];
      min_mse = 9999;
      bef_length = 0;
      bef_start = now_start-1;
      while(bef_length < M){
        if(min_mse > dp[bef_start][now_start-1]){
          min_mse = dp[bef_start][now_start-1];
        }
      }
      now_line_start -= 1;
      now_line_length += seq[now_line_start];
    }
  }  
  return 0;
}
