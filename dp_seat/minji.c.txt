#include <stdio.h>
 
int main(){
    int N,M;
    int chair[41] = {0, };
    int arr[41] = {0, };
    int ans=1;
    arr[0] = 1;
    arr[1] = 1;
    arr[2] = 2;
    scanf("%d %d",&N,&M);
    for(int i=3;i<=N;i++){
        arr[i] = arr[i-1] + arr[i-2];
    }
    for(int i=1;i<=M;i++){
        scanf("%d",&chair[i]);
        ans *= arr[chair[i] - chair[i-1]-1];
    }
    if(chair[M] != N){
        ans *= arr[N-chair[M]];
    }
    printf("%d",ans);
    return 0;
}