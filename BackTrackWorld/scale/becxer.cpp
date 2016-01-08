#include <iostream>                                                                
                                                                                    
int ruby[31];                                                                      
int map[31][301];                                                                  
using namespace std;                                                               
int main(void){                                                                    
    int n,sum;                                                                     
    cin >> n;                                                                      
    sum = 0;                                                                       
    for(int i = 0 ; i < n ; i++){                                                  
         cin >> ruby[i];                                                           
         sum += ruby[i];                                                           
         map[i][ruby[i]] += 1;                                                     
         for(int r = 0; r < 300; r++){                                             
            if( i-1 >= 0 && map[i-1][r] >= 1){                                     
                map[i][r] += map[i-1][r];                                          
                map[i][r+ruby[i]] += map[i-1][r];                                  
            }                                                                      
         }                                                                         
    }                                                                              
    if(sum % 2 == 1 || map[n-1][sum/2] == 0) cout << "impossible" << endl;         
    else cout << map[n-1][sum/2] << endl;                                       
    return 0;                                                                      
}
