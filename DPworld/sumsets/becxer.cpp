#include <iostream>
#define MAX_COUNT 1000001
#define MAX_P 20

using namespace std;

int E[MAX_P][MAX_COUNT];
int power[MAX_P];

int main(void){
    power[0] = 1;
    int N; cin >> N;

    for(int i = 0; i < MAX_COUNT; i++) E[0][i] = 1;

    for(int j = 1; j < MAX_P; j++){
        E[j][0] = 1;
        E[j][1] = 1;
        power[j] = power[j-1] * 2;
    }

    for(int n = 1 ; n <= N ; n++){
        for(int p = 1 ; p < MAX_P ; p++){
            E[p][n] = 0;

            if( power[p] > n ) {
                E[p][n] = E[p-1][n];
                continue;
            }

            for(int q = 0; q <= p ; q++){
               E[p][n] += E[q][n-power[q]];
               E[p][n] %= 1000000000;
            }
        }
    }
    cout << E[MAX_P-1][N] % 1000000000 << endl;
    return 0;
}
