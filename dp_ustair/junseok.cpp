#include<iostream>
 
using namespace std;
 
int main(){
    int tc,n,i,j,tmp_M=0;
     
     
        int A[305]={0};                                 
        int B[305]={0};                 
        int C[305]={0};                 
        int M[305]={0};
        tmp_M=0;
        cin>>n;
        for(j=3;j<=n+2;j++){
            cin>>A[j];
            B[j]=M[j-2]+A[j];
            C[j]=B[j-1]+A[j];
            if(B[j]>C[j]){
                tmp_M=B[j];
            }
            else{
                tmp_M=C[j];
            }
            M[j]=tmp_M;
            //cout<<B[j]<<" "<<C[j]<<" "<<M[j]<<endl;
        }
        if(B[j-1]>C[j-1]){
            cout<<B[j-1]<<endl;
         }
         else{
            cout<<C[j-1]<<endl;
         }
 
}