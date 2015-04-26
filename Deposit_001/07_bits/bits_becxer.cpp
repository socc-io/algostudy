#include <iostream>

using namespace std;

int n, m;
long long arr[100];
int res = 1;

int main(void){
    cin >> n >> m;
    arr[0] = 1;
    for(int i = 1 ; i <= m ; i++){
        arr[i] = (n-i+1) * arr[i-1] / i;
        res += arr[i];
    }   
    
    cout << res << endl;
}
