#include <iostream>
using namespace std;
int dp[301][2];
int main(void){
  int N; cin >> N;
  dp[0][0] = 0; dp[0][1] = 0;
  cin >> dp[1][0]; dp[1][1] = dp[1][0];
  for(int i = 2 ; i <= N ; i++ ){
    int now_step; cin >> now_step;
    dp[i][0] = 0; dp[i][1] = 0;
    if(i-1 >= 0) {
      dp[i][1] = (dp[i][1] > dp[i-1][0])? dp[i][1] : dp[i-1][0];
      dp[i][1] += now_step;
    } 
    if(i-2 >= 0) {
      dp[i][0] = (dp[i][0] > dp[i-2][0])? dp[i][0] : dp[i-2][0];
      dp[i][0] = (dp[i][0] > dp[i-2][1])? dp[i][0] : dp[i-2][1];
      dp[i][0] += now_step;
    }
  }

  cout << ((dp[N][0] > dp[N][1])? dp[N][0] : dp[N][1]) << endl;
  return 0;
}
