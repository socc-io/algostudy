#include <iostream>

using namespace std;

#define MOD (100000000000000000)

void hanoi_print(int N, int from, int to)
{
    if(N <= 0) return;
    int mid = 3 - from - to;
    hanoi_print(N-1, from, mid);
    printf("%d %d\n", from+1, to+1);
    hanoi_print(N-1, mid, to);
}

int main(void)
{
    int N;
    scanf("%d", &N);
    unsigned long long buf[2], tmp;
    buf[0] = 1;
    buf[1] = 0;
    for(int i=1; i<N; ++i) {
        buf[0] = (buf[0]<<1) + 1;
        buf[1] <<= 1;
        if(buf[0] >= MOD) {
            buf[0] -= MOD;
            ++buf[1];
        }
    }
    if(buf[1] > 0) {
        printf("%llu", buf[1]);
        // get log10(buf[0])
        tmp = buf[0];
        int lg_buf0 = 0;
        while(tmp) {
            ++lg_buf0;
            tmp /= 10;
        }
        // print zeros
        for(int i=0; i<17-lg_buf0; ++i) {
            putchar('0');
        }
    }
    printf("%llu\n", buf[0]);
    if(N <= 20) hanoi_print(N, 0, 2);
}
