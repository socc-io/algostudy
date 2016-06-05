#include <iostream>

using namespace std;

int dp[10001]; int M,N;
int word[10001];
int main(void){
  cin >> M >> N;
  for(int i = 0 ; i < N ; i++){
    cin >> word[i];
    dp[i] = 999999999;
  }

  dp[0] = (M - word[0]) * (M - word[0]);

  for(int i = 1 ; i < N ; i++){
    int line_length = word[i];
    int include_word = i;
    while(line_length <= M && include_word >= 0){
      int now = -1;
      if(include_word == 0){
        now = (M - line_length) * (M - line_length);
      }else{
        now = (M - line_length) * (M - line_length) + dp[include_word-1];
      }
      if(now <= dp[i]){
        dp[i] = now;
      }
      include_word = include_word - 1;
      line_length += word[include_word] + 1;
    }
  }

  cout << dp[N-1] << endl;
  
  return 0;
}
