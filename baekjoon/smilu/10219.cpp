#include<iostream>
using namespace std;

char buf[12][12];

int main()
{
    int T;
    scanf("%d", &T);
    while(T--) {
        int n, m;
        scanf("%d%d", &n, &m);
        for(int i=0; i<n; ++i) {
            scanf("%s", buf[i]);
        }
        for(int i=0; i<n; ++i) {
            for(int j=0; j<m; ++j) {
                putchar(buf[i][m-1-j]);
            }
            putchar('\n');
        }
    }
}
