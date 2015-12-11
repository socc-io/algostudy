#include <iostream>                                                             
using namespace std;                                                            
                                                                                
int degree = 1;                                                                 
int sum = 0;                                                                    
int maxim = 0;                                                                  
int minim = 0;                                                                  
int now = 0;                                                                    
int past = 0;                                                                   
int main(void){                                                                 
    int n;                                                                      
    cin >> n;                                                                   
    for(int i = 0; i < n ;i++){                                                 
        cin >> now;                                                             
        int now_degree = now - past;                                            
        if(degree > 0 && now_degree > 0){                                       
            maxim = now;                                                        
        }else if(degree > 0 && now_degree < 0){                                 
            sum += maxim;                                                       
            minim = now;                                                        
        }else if(degree < 0 && now_degree < 0){                                 
            minim = now;                                                        
        }else if(degree < 0 && now_degree > 0){                                 
            sum -= minim;                                                       
            maxim = now;                                                        
        }                                                                       
                                                                                
        if( past != now ){                                                      
            past = now;                                                         
            degree = now_degree;                                                
        }                                                                       
    }                                                                           
    if(degree > 0){                                                             
        sum += now;                                                             
    }                                                                           
    cout << sum << endl;                                                        
    return 0;                                                                   
}    
