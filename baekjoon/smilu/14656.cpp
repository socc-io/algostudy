#include <cstdio>

int N;

int main(void)
{
    scanf("%d", &N);
    int tmp;
    int cnt = 0;
    for(int i=0; i<N; ++i) {
        scanf("%d", &tmp);
        if(tmp != i+1) ++cnt;
    }
    printf("%d", cnt);
}
