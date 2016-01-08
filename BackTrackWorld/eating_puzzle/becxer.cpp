#include <iostream>                                                             
                                                                                 
int food[22];                                                                   
int foodsum[22][100000];                                                        
using namespace std;                                                            
int main(void){                                                                 
    int limit, n,sum;                                                           
    cin >> limit >> n;                                                          
    sum = 0;                                                                    
    for(int i = 0 ; i < n ; i++){                                               
         cin >> food[i];                                                        
         sum += food[i];                                                        
         foodsum[i][food[i]] += 1;                                              
         for(int r = 0; r <= limit; r++){                                       
            if( i-1 >= 0 && foodsum[i-1][r] >= 1){                              
                foodsum[i][r] += foodsum[i-1][r];                               
                foodsum[i][r+food[i]] += foodsum[i-1][r];                       
            }                                                                   
         }                                                                      
    }                                                                           
                                                                                 
    for(int k = limit; k >= 0 ; k--){                                           
        if(foodsum[n-1][k] > 0){                                                
            cout << k << endl;                                                  
            break;                                                              
        }                                                                       
    }                                                                           
    return 0;                                                                   
}
