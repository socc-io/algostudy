#include<iostream>
#include<algorithm>
using namespace std;

int main()
{
    int n, k;
    scanf("%d%d", &n, &k);
    int l = 1, r = k;
    while(l <= r) {
        long long c = 0;
        int m = (l + r) / 2;
        for(int i=1; i<=n; ++i) c += min(n, m/i);
        if(c < k) l = m+1;
        else r = m-1;
    }
    printf("%d", l);
}
