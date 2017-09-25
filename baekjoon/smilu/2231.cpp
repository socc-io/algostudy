#include<cstdio>

int f(int val)
{
    int ans = val;
    while(val) {
        ans += val % 10;
        val /= 10;
    }
    return ans; 
}

int main()
{
    int n;
    scanf("%d", &n);
    for(int i=0; i<=n; ++i) {
        if(f(i) == n) {
            printf("%d", i);
            return 0;
        }
    }
    puts("0");
}
