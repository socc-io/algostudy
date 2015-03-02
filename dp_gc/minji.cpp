#include <stdio.h>
 
//2*n개의 모서리
//겹치지 않게 n개의 선 긋는 방법
/*
n   ans
3   !2 +  !1 * !1   +                                 !2
4   !3 +  !1 * !2   +                      !2 * !1  + !3
5   !4 +  !1 * !3   + !2 * !2  +           !3 * !1  + !4
6   !5 +  !1 * !4   + !2 * !3  + !3 * !2 + !4 * !1  + !5
*/
 
int main(){
    int n;
    scanf("%d",&n);
    int ans[20] = {0, };
    ans[1] = 1;
    ans[2] = 2;
    if(n >= 3){
        for(int i=3;i<=n;i++){
            for(int j = 1; j<= i-2 ; j++){
                ans[i] = ans[i] + (ans[j] * ans[i-j-1]); 
            }
            ans[i] += ans[i-1] + ans[i-1];
        }
    }
    printf("%d",ans[n]);
    return 0;
}