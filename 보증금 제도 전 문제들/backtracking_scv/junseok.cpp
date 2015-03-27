#include<iostream>//B
 
using namespace std;
 
int n;  
int A[105][105] = {0};
int B[105][105] = {0};
 
void Scv(int i,int j){
    int up = 0 , left = 0;
    up = A[i][j] + B[i-1][j];
    left = A[i][j] + B[i][j-1];
    if( up >= left){
        B[i][j] = up;
    }
    else{
        B[i][j] = left;
    }
}
 
int main(){
    int i,j;
    cin >> n;
    for( i = 1; i<=n ; i++){
        for( j = 1; j<=n ;j++){
            cin >> A[i][j];
                    Scv(i , j);     
                }
    }
    cout<<B[i-1][j-1]<<endl;
}