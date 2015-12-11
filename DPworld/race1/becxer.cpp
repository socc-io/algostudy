#include <iostream>
 
int spot[103][2]; // 0:거리 1:걸리는시간
int min_fix_t[103];
 
using namespace std;
int main(void){
 
    for (int i = 0; i < 103; i++){
        spot[i][0] = 0;
        spot[i][1] = 0;
        min_fix_t[i] = 99999999;
    }
 
    int len, n;
    cin >> len >> n;
 
    for (int i = 0; i < n + 1; i++){
        cin >> spot[i][0];
    }
    for (int i = 1; i < n + 1; i++){
        cin >> spot[i][1];
    }
    spot[n + 1][1] = 0;
    min_fix_t[0] = 0;
 
    for (int i = 0; i < n + 2; i++){
        int coverage = 0;
        for (int p = i-1; p >= 0; p--){
            coverage += spot[p][0];
            if (coverage > len) break;
            int now_fix = min_fix_t[p] + spot[i][1];
            if (now_fix <= min_fix_t[i]){
                min_fix_t[i] = now_fix;
            }
        }
    }
 
    cout << min_fix_t[n + 1] << endl;
    return 0;
}
