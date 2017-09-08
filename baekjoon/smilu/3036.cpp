#include<iostream>
using namespace std;

int n;
int sz[100];

int gcd(int a, int b)
{
    if(a<b) swap(a,b);
    while(b) {
        int tmp = a%b;
        a=b;
        b=tmp;
    }
    return a;
}

int main()
{
    scanf("%d", &n);
    for(int i=0; i<n; ++i) {
        scanf("%d", sz+i);
    }
    for(int i=1; i<n; ++i) {
        int g = gcd(sz[0], sz[i]);
        printf("%d/%d\n", sz[0]/g, sz[i]/g);
    }
}
