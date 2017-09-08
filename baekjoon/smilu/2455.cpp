#include<cstdio>

int main(void)
{
    int p = 0, a, b;
    int max_p = -1;
    for(int i=0; i<4; ++i) {
        scanf("%d%d", &a, &b);
        p += b-a;
        if(max_p < p) max_p = p;
    }
    printf("%d", max_p);
}

