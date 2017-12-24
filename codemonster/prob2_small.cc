#include<iostream>
#include<algorithm>
using namespace std;

#define MAXN 503

int n;
bool b[MAXN][MAXN];
int rdfs[MAXN][MAXN];
int ldfs[MAXN][MAXN];

void do_task()
{
    scanf("%d", &n);
    for(int i=n; i>0; --i) {
        for(int j=1; j<=n; ++j) {
            getchar();
            b[j][i] = (getchar() == 'B');
        }
    }
    for(int i=0; i<=n+1; ++i) {
        rdfs[i][0] = 0;
        rdfs[0][i] = 0;
        rdfs[i][n+1] = 0;
        rdfs[n+1][i] = 0;
        ldfs[i][0] = 0;
        ldfs[0][i] = 0;
        ldfs[i][n+1] = 0;
        ldfs[n+1][i] = 0;
    }
    for(int i=1; i<=n; ++i) {
        for(int j=1; j<=n; ++j) {
            rdfs[i][j] = b[i][j] + max(rdfs[i-1][j], rdfs[i][j-1]);
        }
    }
    for(int i=1; i<=n; ++i) {
        for(int j=n; j>0; --j) {
            ldfs[i][j] = b[i][j] + max(rdfs[i-1][j], max(ldfs[i-1][j], ldfs[i][j+1]));
        }
    }
    printf("%d\n", ldfs[n][1]); 
}

int main()
{
    int T;
    scanf("%d", &T);
    while(T--) do_task();
}
