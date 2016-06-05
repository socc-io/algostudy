#include <iostream>
 
using namespace std;
 
int dp[41][40001][2]; // 0 is from where, 1 is maxium hieght
 
int main(void){
    int N,bit; cin >> N;
 
  for(int i = 0; i < N; i++){
        for(int p = 0; p < 1000 * (i+1) ; p++){
                dp[i][p][0] = -1;
      dp[i][p][1] = 40001;
    }
  }
   
  for(int i = 0; i < N; i++){
    cin >> bit;
    if(i == 0){
      dp[i][bit][0] = 0;
      dp[i][bit][1] = bit;
      continue;
    }
    for(int p = 0; p < i * 1000 ; p++){
      for(int pm = -1; pm <= 1 ; pm+=2){
                int pbit = p + pm * bit;
        if(pbit >= 0 && dp[i-1][pbit][0] >= 0){
                    if(dp[i][p][1] > dp[i-1][pbit][1] && dp[i-1][pbit][1] >= p){
                                  dp[i][p][1] = dp[i-1][pbit][1];
            dp[i][p][0] = pbit;
          }else if( p > dp[i-1][pbit][1]){
            dp[i][p][1] = p;
            dp[i][p][0] = pbit;
          }
        }
      }
    }
  }
  if(dp[N-1][0][0] >= 0){
    int now = 0;
    char ud[41];
    ud[N] = '\0';
    for(int i = N-1 ; i >= 0 ; i--){
      int prev = dp[i][now][0];
      if(now - prev > 0){
        ud[i] = 'U';
      }else{
        ud[i] = 'D';
      }
      now = prev;
    }
    cout << ud << endl;
  }else{
    cout << "IMPOSSIBLE" << endl;
  }
  return 0;
}
                    }
        }
      }
        }
  }
}
