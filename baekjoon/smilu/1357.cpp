#include<cstdio>

int Rev(int X)
{
    int res=0;
    while(X) {
        res = res*10 + (X%10);
        X /= 10;
    }
    return res;
}
int main(void)
{
    int a, b;
    scanf("%d%d", &a, &b);
    printf("%d", Rev(Rev(a) + Rev(b)));
}
