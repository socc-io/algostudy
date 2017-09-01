#include <cstdio>

int a[15];

int main(void)
{
    int tmp;
    while(1) {
        int len = 0;
        while(1) {
            scanf("%d", &tmp);
            if(tmp == -1) return 0;
            if(tmp == 0) break;
            a[len++] = tmp;
        }
        int cnt = 0;
        for(int i=0; i<len; ++i) {
            for(int j=0; j<len; ++j) {
                if(a[i]*2 == a[j]) {
                    ++cnt;
                    break;
                }
            }
        }
        printf("%d\n", cnt);
    }
}
