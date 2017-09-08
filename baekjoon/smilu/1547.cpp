#include<iostream>
using namespace std;

int main()
{
    int n;
    scanf("%d", &n);
    int ball = 1;
    for(int i=0; i<n; ++i) {
        int a, b;
        scanf("%d%d", &a, &b);
        if(a == ball) ball = b;
        else if(b == ball) ball = a;
    }
    printf("%d", ball);
}
