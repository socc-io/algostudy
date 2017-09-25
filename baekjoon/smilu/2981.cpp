#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;

int n;
int a[100];
int buf[100000];
int bl;

int gcd(int a, int b)
{
    if(a<b) swap(a,b);
    while(b) {
        int tmp = a%b;
        a = b;
        b = tmp;
    }
    return a;
}

int main()
{
    scanf("%d", &n);
    for(int i=0; i<n; ++i) scanf("%d", a+i);
    sort(a, a+n);
    int g = a[1]-a[0];
    for(int i=2; i<n; ++i) g = gcd(g, a[i]-a[i-1]);
    for(int i=2; i*i<=g; ++i) if(g%i == 0) {
        buf[bl++] = i;
        buf[bl++] = g/i;
        if(i*i == g) --bl;
    }
    buf[bl++] = g;
    sort(buf, buf+bl);
    for(int i=0; i<bl; ++i) printf("%d ", buf[i]);
}

