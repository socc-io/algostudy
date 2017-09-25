#include<iostream>
using namespace std;

typedef unsigned long long lld;

int main()
{
    lld n;
    scanf("%lld", &n);
    lld ans = n;
    for(lld div=2; div<=n; ++div) {
        if(div*div > n) div=n;
        if(n % div) continue;
        ans = (ans / div) * (div-1);
        while(!(n % div)) n /= div;
    }
    printf("%lld", ans);
}
