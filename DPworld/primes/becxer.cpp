#include <iostream>

using namespace std;

int now_prime = 2;
int get_next_prime(){
  for(int i = now_prime+1; i <= 10001; i++){
    bool divided = false;
    for(int j = 2; j < i ; j++){
      if(i % j == 0) {
        divided = true;
        break;
      }
    }
    if (divided) continue;
    now_prime = i;
    return now_prime;
  }
  return 0;
}

int dp[2][10001];
int res[10001];
int max_dp = 0;

int main(void){
  dp[0][0] = 1; dp[0][2] = 1; res[2] = 1; max_dp = 2;
  for(int i = 1; i <= 1228 ; i++){
    int np = get_next_prime();
    dp[i%2][0] = 1;
    for(int c = 1; c <= max_dp + np && c <= 10000 ; c++){
      if(c - np >= 0 && dp[(i-1)%2][c-np] > 0){
        dp[i%2][c] = dp[(i-1)%2][c-np]; res[c] += 1;
      }else{
        dp[i%2][c] = 0;
      }
    }
    max_dp += np;
  }

  while(true){
    int inp; cin >> inp;
    if(inp == 0) break;
    cout << res[inp] << endl;
  }
  return 0;
}
