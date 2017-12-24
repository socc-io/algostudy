#include<iostream>
using namespace std;

typedef long long lld;

lld a[10000];
lld k, n;

bool check(lld val)
{
    lld nn = 0;
    for(int i=0; i<k; ++i) {
        nn += a[i] / val;
    }
    return nn >= n;
}

int main()
{
    scanf("%lld%lld", &k, &n);
    lld r = -1, l = 1;
    for(lld i=0; i<k; ++i) {
        scanf("%lld", a+i);
        if(a[i] > r) r = a[i];
    }
    while(1) {
        lld mid = (l+r)>>1;
        if(check(mid)) {
            if(l == mid) break;
            l = mid;
        } else {
            if(r == mid) break;
            r = mid;
        }
    }
    printf("%lld", check(r) ? r : l);
}
