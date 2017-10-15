#include<cstdio>

int n, m, k;
void f(int x, int y) {
    if(y == m) printf("%d ", k-x);
    else {
        printf("%d ", x);
        f(x+y, y*2);
        f(x+y+y, y*2);
    }
}

int main()
{
    scanf("%d", &n);
    m = (1 << (n-1));
    k = m*3-1;
    f(1, 1);
}
