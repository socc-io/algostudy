#include <iostream>
#define MAX_COUNT 51
#define MAX_P 51

using namespace std;

int E[MAX_P][MAX_COUNT];
int pin[MAX_P];

int main(void){
        pin[0] = 1;
        int N; cin >> N;

        for (int i = 0; i < MAX_COUNT; i++) E[0][i] = 1;

        for (int j = 1; j < MAX_P; j++){
                E[j][0] = 1;
                E[j][1] = 1;
                pin[j] = pin[j - 1] + 1;
        }

        for (int n = 1; n <= N; n++){
                for (int p = 1; p < MAX_P; p++){
                        E[p][n] = 0;

                        if (pin[p] > n) {
                                E[p][n] = E[p - 1][n];
                                continue;
                        }

                        for (int q = 0; q <= p; q++){
                                E[p][n] += E[q][n - pin[q]];
                        }
                }
        }
        cout << E[MAX_P - 1][N]<< endl;
        return 0;
}
