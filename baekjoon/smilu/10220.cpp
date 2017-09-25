#include<cstdio>

const int k[] ={0, 0, 0, 0, 2, 1, 0};

int main()
{
    int T, n;
    scanf("%d", &T);
    while(T--) {
       scanf("%d", &n);
       printf("%d\n", n <= 6 ? k[n] : 1);
    } 
}
