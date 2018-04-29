#include <iostream>

using namespace std;

int main(void){
  int N, pang[1001], dp[1001];
  cin >> N;

  for(int i = 1 ; i <= N ; i+=1){
    cin >> pang[i];
    dp[i] = pang[i];
  }
  
  for(int i = 2 ; i <= N ; i+=1){
    int from_x = 1;
    while( i - from_x >= 1){
      int bef_x = i - from_x;
      if(dp[bef_x] + pang[from_x] > dp[i]){
        dp[i] = dp[bef_x] + pang[from_x];
      }
      from_x += 1; 
    }
  }
  cout << dp[N] <<endl;  
  return 0;
}
