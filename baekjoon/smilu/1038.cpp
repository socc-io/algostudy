#include<iostream>
using namespace std;

int dp[12][10];
int sum[12];

int main()
{
    int n;
    scanf("%d", &n);
    for(int i=0; i<12; ++i) dp[i][0] = 0;
    dp[1][0] = 1;
    for(int i=1; i<12; ++i) {
        for(int j=1; j<10; ++j) {
            dp[i][j] = dp[i][j-1] + dp[i-1][j-1];
        }
    }
    for(int i=1; i<12; ++i) {
        for(int j=0; j<10; ++j) {
            sum[i] += dp[i][j];
        }
        sum[i] += sum[i-1];
    }
    int sz = 1;
    while(sz < 12 && sum[sz] <= n) ++sz;
    if(sz == 12 ) {
        puts("-1");
        return 0;
    }
    n -= sum[sz-1];
    for(int i=sz; i>0; --i) {
        for(int j=0; j<10; ++j) {
            n -= dp[i][j];
            if(n < 0) {
                n += dp[i][j];
                putchar('0'  + j);
                break;
            }
        }
    }
    
}

