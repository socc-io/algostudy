#include <cstdio>
#include <cstring>

char S[21];

int main(void)
{
    scanf("%s", S);
    int len = strlen(S);
    int m = (len+1)>>1;
    for(int i=0; i<m; ++i) {
        if(S[i] != S[len-1-i]) {
            puts("false");
            return 0;
        }
    }
    puts("true");
}
