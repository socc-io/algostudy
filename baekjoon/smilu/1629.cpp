#include<cstdio>
int main()
{
    long long r=1,a,b,c;
    scanf("%lld%lld%lld",&a,&b,&c);
    while(b) {
        if(b&1){r=r*a%c;}
        a=a*a%c;
        b>>=1;
    }
    printf("%lld",r);
}
