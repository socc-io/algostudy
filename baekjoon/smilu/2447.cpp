#include<iostream>
using namespace std;

void print(int scale, int line)
{
    if(scale == 1) {
        putchar('*');
        return;
    }
    int scale3 = scale/3;
    if(line < scale3 || scale3*2 <= line) {
        line %= scale3;
        print(scale3, line);
        print(scale3, line);
        print(scale3, line);
    } else {
        line %= scale3;
        print(scale3, line); 
        for(int i=0; i<scale3; ++i) putchar(' ');
        print(scale3, line);
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    for(int i=0; i<n; ++i) {
        print(n, i);
        putchar('\n');
    }
}
