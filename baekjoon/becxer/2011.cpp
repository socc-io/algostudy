#include <iostream>
#include <string>

using namespace std;

int cnt[5001];

int main(void){
  string input;
  cin >>input;
  for(int i=0; i <= input.size(); i++) cnt[i] = 0;
  cnt[0] = 1;
  cnt[1] = 1;
  
  bool impossible = true;
  if(input[0] == '0'){
    cout << 0 << endl;
    return 0;
  }
    
  for(int i=2; i <= input.size(); i++){
    if(input[i-1] != '0') {
        cnt[i] += cnt[i-1];
    }
    if(input[i-2] >= '1' && (input[i-2]-'0') * 10 + (input[i-1]-'0') <= 26){
      cnt[i] += cnt[i-2];
    }
    cnt[i] = cnt[i] % 1000000;
  }

  cout << cnt[input.size()] << endl;
  return 0;
}
