#include<cstdio>

int main(void)
{
    long long n,m;
    scanf("%lld%lld", &n, &m);
    if(n-m < m) m = n-m;
    long long t_cnt=0, f_cnt=0;
    for(long long i=2; i <= n; i=i*2) {
        t_cnt += n/i - m/i - (n-m+i)/i + 1; 
    }
    for(long long i=5; i <= n; i=i*5) {
        f_cnt += n/i - m/i - (n-m+i)/i + 1;
    }
    printf("%lld", t_cnt < f_cnt ? t_cnt : f_cnt);
}
     
