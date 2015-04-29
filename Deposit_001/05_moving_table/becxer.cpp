#include <iostream>

using namespace std;
int n;
int cnt[400] = {0};
int start[400] = {0};
int endf[400] = {0};

int main(void){
    cin >> n;
    for(int i = 0 ; i < n ; i ++){
        int s,e,tmps,tmpe;
        cin >> s >> e;
        tmps = (s % 2 == 0)? s/2 : (s+1)/2;
        tmpe = (e % 2 == 0)? e/2 : (e+1)/2; 
        start[i] = (tmps <= tmpe)? tmps:tmpe;
        endf[i] = (tmps <= tmpe)? tmpe:tmps;
        for(int j = start[i] ; j <= endf[i] ; j++){
            cnt[j]+=1; 
        }   
    }   
 
    int max = 0;
    for(int i = 0; i <= 400 ; i++){
        max = (max < cnt[i])? cnt[i] : max;
    }   
    cout << max * 10 <<endl;
    return 0;
}
