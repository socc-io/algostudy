#include<iostream>
using namespace std;

char buf[101];

int main()
{
    scanf("%s", buf);
    for(char* ch=buf; *ch != '\0'; ++ch) {
        if('A' <= *ch && *ch <= 'Z') {
            putchar(*ch);
        }
    }
}
