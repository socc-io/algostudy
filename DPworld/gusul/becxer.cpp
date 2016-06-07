#include <iostream>

using namespace std;

int b[3];
int k1,k2;

bool dp[501][501]; // true is win, false is lose

int main(void){
  cin >> b[0] >> b[1] >> b[2];
  for(int i = 0 ; i < 501 ; i++)
    for(int j = 0 ; j < 501 ; j++)
      dp[i][j] = false;

  for(int i = 0 ; i < 501; i++){
    for(int j = 0; j < 501; j++){
      bool can_get = false;
      bool send_losing = false;
      for(int bx = 0 ; bx < 3 ; bx++){
        if(i-b[bx] >= 0){
          can_get = true;
          if(dp[i-b[bx]][j] == false){
            send_losing = true;
          }
        }
        if(j-b[bx] >= 0){
          can_get = true;
          if(dp[i][j-b[bx]] == false){
            send_losing = true;
          }
        }
      }
      if(!can_get || (can_get && !send_losing)){
        dp[i][j] = false;
      }else{
        dp[i][j] = true;
      }  
    }
  }

  for(int i = 0; i < 5 ; i++){
    cin >> k1 >> k2 ;
    if(dp[k1][k2]) cout << "A" << endl;
    else cout << "B" << endl;
  }
  
  return 0;
}
