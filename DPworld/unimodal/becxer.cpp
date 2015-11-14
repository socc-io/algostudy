#include <iostream>
#define MAX 251
using namespace std;

// X :: End  , Y :: LENGTH
long long arr[MAX][MAX];

int main(void){
    int n;
    cin >> n;
    arr[1][1] = 1;
    arr[2][1] = 1;
    arr[2][2] = 1;
    for(int l = 3 ; l < MAX ; l++){
        for(int e = 1 ; e < MAX ; e++){
            if(l == e || l == 2*e || l == 3 * e){
                arr[l][e] = 1;
            }else if (l < 3 * e){
                arr[l][e] = 0;
            }else{
                arr[l][e] = 0;
                for(int i = e; i <= l-2*e; i++){
                    arr[l][e] += arr[l-2*e][i];
                }
            }
        }
    }

    long long res = 0;
    for(int i = 1; i <= n; i++){
        res += arr[n][i];
    }

    cout << res << endl;
    
    return 0;
}
