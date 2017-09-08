#include<cstdio>
#include<cmath>

int main(void)
{
    long long n;
    scanf("%lld", &n);
    printf("%d", (int)((sqrt(8*n+1)-1.)/2.));
}
