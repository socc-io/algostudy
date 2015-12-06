#include <iostream>                                                             
                                                                                
int New[10001];                                                                 
int All[1000001];                                                               
                                                                                
using namespace std;                                                            
int main(void){                                                                 
        int a, b, d, N;                                                         
        cin >> a >> b >> d >> N;                                                
        New[0] = 1; All[0] = 1;                                                 
        for (int i = 1; i <= N; i++){                                           
                New[i] = (((i >= 2)? New[i - 1] : 0)                            
                        + ((i >= a) ? New[i - a] : 0)                           
                        - ((i >= b)? New[i - b] : 0)) % 1000;                   
                All[i] = (All[i - 1] + New[i]                                   
                        - ((i >= d) ? New[i - d] : 0)) % 1000;                  
        }                                                                       
        cout << ((All[N] < 0)? 1000 + All[N] : All[N]) << endl;                 
        return 0;                                                               
}  
