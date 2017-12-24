#include<iostream>
using namespace std;

int main()
{
    int n;
    scanf("%d", &n);
    int m[3];
    int M[3];
    int b[3];
    for(int i=0; i<n; ++i) {
        int a[3];
        scanf("%d%d%d", a, a+1, a+2);
        if(i == 0) {
            m[0] = M[0] = a[0];
            m[1] = M[1] = a[1];
            m[2] = M[2] = a[2];
        } else {
            b[0] = min(m[0], m[1]);
            b[1] = min(b[0], m[2]);
            b[2] = min(m[1], m[2]);
            m[0] = a[0] + b[0];
            m[1] = a[1] + b[1];
            m[2] = a[2] + b[2];
            b[0] = max(M[0], M[1]);
            b[1] = max(b[0], M[2]);
            b[2] = max(M[1], M[2]);
            M[0] = a[0] + b[0];
            M[1] = a[1] + b[1];
            M[2] = a[2] + b[2];
        }
    }
    printf("%d %d\n", max(max(M[0], M[1]), M[2]), min(min(m[0], m[1]), m[2]));
}
