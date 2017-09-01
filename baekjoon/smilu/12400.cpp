#include <cstdio>
#include <cstring>

const char *dict = "yhesocvxduiglbkrztnwjpfmaq";

int main(void)
{
    int T;
    scanf("%d", &T); getchar();
    for(int t=1; t<=T; ++t) {
        printf("Case #%d: ", t);
        char ch;
        while((ch = getchar()) != '\n') {
            if(ch == ' ') putchar(' ');
            else {
                putchar(dict[ch -'a']);
            }
        }
        putchar('\n');
    }
}
