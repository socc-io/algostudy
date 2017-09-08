#include<cstdio>
int main()
{
    long long n;
    scanf("%lld", &n); ++n;
    printf("%lld", ((3*n*n-n)/2)%45678);
}
