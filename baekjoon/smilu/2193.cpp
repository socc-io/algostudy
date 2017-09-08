#include <iostream>

using namespace std;

long long d[91][2];

int main(void)
{
    d[1][1] = 1;
    d[1][0] = 1;
    int N;
    scanf("%d", &N);
    for(int i=2; i<=N; ++i) {
        d[i][1] = d[i-1][0];
        d[i][0] = d[i-1][1] + d[i-1][0];
    }
    printf("%lld", d[N][1]);
} 
