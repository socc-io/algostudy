#include <iostream>
#define EXIST 1
#define NONE 0
 
using namespace std;
 
int money[101][30001][2]; // 0 : money exist , 1 : collect sequence
int N, coin, max_money;
 
int main(void){
   
  for(int i = 0 ; i < 101 ; i++){
        for(int j = 0 ; j < 30001 ; j++){
                money[i][j][0] = NONE;
      money[i][j][1] = 0;
    }
  }
  money[0][0][0] = EXIST;
 
  cin >> N;
  for(int i = 1 ; i <= N ; i++){
    cin >> coin;
    for(int j = 0 ; j < 30001 ; j++){
      money[i][j][0] = money[i-1][j][0];
      if(money[i][j][0] == EXIST){
                money[i][j][1] = 0;
        continue;
      }
 
      if(j >= coin && money[i-1][j - coin][0] == EXIST){
         if(money[i-1][j-coin][1] < 2){
                      money[i][j][0] = EXIST;
           money[i][j][1] = money[i-1][j-coin][1] + 1;
 
           max_money = (j > max_money)? j : max_money;
         }
      }
    }
  }
 
  cout << max_money << endl;
 
  return 0;
}
