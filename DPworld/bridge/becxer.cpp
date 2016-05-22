#include <iostream>
#include <cstring>

using namespace std;

int bridge[2][21][101];
char bstr[2][101];
char step[21];
int main(void)
cin >> step >> bstr[0] >> bstr[1];
int step_size = strlen(step);
int str_size =  strlen(bstr[0]);
int res = 0;
for(int row = 0 ; row < step_size ; row ++){
  for(int br = 0; br < 2 ; br++){
    int br_oth = (br + 1) % 2; 
    for(int col = 0; col < str_size ; col ++){
        if(row == 0){
           if(step[row] == bstr[br][col]){
             bridge[br][row][col] = 1;
           }else{
             bridge[br][row][col] = 0;
           }
        }else{
          if(step[row] == bstr[br][col]){
            for (int col_oth = 0 ; col_oth < col ; col_oth++){
              bridge[br][row][col] += bridge[br_oth][row-1][col_oth];
            }
          }
        }
        res += (row == step_size-1)? bridge[br][row][col] : 0;
    }
  }
 }
 cout << res << endl;
 return 0;
}
