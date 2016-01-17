#include <iostream>                                                             
using namespace std;                                                            
int point[13][2];                                                               
int abs(int x){ return (x < 0)? -1 * x : x; }                                   
int menhattan_distance(int p1, int p2){                                         
    return abs(point[p1][0] - point[p2][0]) + abs(point[p1][1] - point[p2][1]); 
}                                                                                  
                                                                                    
class Path{                                                                        
public:                                                                            
    int seq[13];                                                                
    int flag[13];                                                               
    int length;                                                                 
    int count;                                                                  
    Path(){                                                                     
        length = 0; count = 0;                                                  
        this->seq[0] = 0; this->flag[0] = 1;                                    
        for(int i = 1 ; i < 13 ; i++){                                          
            this->seq[i] = 0;                                                   
            this->flag[i] = 0;                                                  
        }                                                                       
        count ++;                                                               
    }                                                                           
    Path(Path* rp, int ns){                                                     
        for(int  i = 0 ; i < 13 ; i++){                                         
            this->seq[i] = rp->seq[i];                                          
            this->flag[i] = rp->flag[i];                                        
        }                                                                       
        this->count = rp->count;                                                
        this->seq[this->count++] = ns;                                          
        this->flag[ns] = 1;                                                     
        this->length = rp->length + menhattan_distance(rp->seq[rp->count-1],ns);
    }                                                                              
};                                                                                 
                                                                                    
template <typename T>                                                              
class Stack{                                                                    
public:                                                                         
    int top;                                                                    
    T* stack_arr[100000];                                                       
    Stack(){top = 0;}                                                           
    void push(T* a){ stack_arr[top++] = a; }                                    
    T* pop(){ return stack_arr[--top]; }                                        
    bool empty(){ return (top == 0)? true:false; }                              
};
 
int main(void){                                                                 
    int trash,n;                                                                
    cin >> trash >> trash;                                                      
    cin >> point[0][0] >> point[0][1] >> n;                                     
    point[n+1][0] = point[0][0]; point[n+1][1] = point[0][1];                   
    for(int i = 1 ; i <= n ; i++){                                              
        cin >> point[i][0] >> point[i][1];                                      
    }                                                                           
                                                                                 
    Stack<Path> st;                                                             
    Path* np = new Path();                                                      
    st.push(np);                                                                
                                                                                 
    int min_path = 99999;                                                       
    while(!st.empty()){                                                         
        Path* now = st.pop();                                                   
        if(now->count == n+1){                                                  
            now = new Path(now, 0);                                             
            min_path = (min_path > now->length)? now->length : min_path;        
        }else{                                                                  
            for(int i = 1 ; i <= n ; i++){                                      
                if(!now->flag[i]){                                              
                    st.push(new Path(now, i));                                  
                }                                                               
            }                                                                      
        }                                                                       
    }                                                                           
                                                                                 
    cout << "The shortest path has length " << min_path << endl;                
    return 0;                                                                   
}  
