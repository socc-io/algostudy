#include <iostream>                                                             
using namespace std;                                                            
int job_end[10001] = {0,};                                                      
int rel[10001][1001];                                                           
int rel_count[10001] = {0,};                                                    
int job_count[10001] = {0,};                                                    
int job_time[10001] = {0,};                                                     
int start_queue[10001];                                                            
int queue_count = 0;                                                               
                                                                                    
int main(void){                                                                    
    int n, up_job;                                                                 
    cin >> n;                                                                      
    for(int i = 0 ; i < n ; i++){                                                  
        cin >> job_time[i] >> job_count[i];                                        
        for(int j = 0; j < job_count[i] ; j++) {                                   
            cin >> up_job ;                                                        
            up_job = up_job -1;                                                    
            rel[up_job][ rel_count[ up_job ] ++ ] = i;                          
        }                                                                       
        if(job_count[i] == 0){                                                  
            start_queue[queue_count++] = i;                                     
        }                                                                       
    }                                                                           
    int max_job_end = 0;                                                        
                                                                                 
    for(int i = 0; i < queue_count ; i++){                                      
        int start = start_queue[i];                                             
        job_end[start] += job_time[start];                                      
        if(max_job_end < job_end[start]){                                       
            max_job_end = job_end[start];                                       
        }                                                                       
                                                                                 
        for (int j = 0 ; j < rel_count[ start ]; j++){                          
            int down = rel[start][j];                                           
            job_count[down] -= 1;                                               
            if(job_end[down] < job_end[start]){                                 
                job_end[down] = job_end[start];                                 
            }                                                                   
            if(job_count[down] == 0){                                           
                start_queue[queue_count++] = down;                              
            }                                                                   
        }                                                                       
    }                                                                           
    cout << max_job_end << endl;                                                
    return 0;                                                                   
}
