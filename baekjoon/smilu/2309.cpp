#include<iostream>
#include<algorithm>
using namespace std;

int t[9];
int ans[7];

int main()
{
    for(int i=0; i<9; ++i) scanf("%d", t+i);
    int ts = 0;
    for(int i=0; i<9; ++i) ts += t[i];
    for(int i=0; i<9; ++i) {
        for(int j=i+1; j<9; ++j) {
            if(ts - t[i] - t[j] == 100) {
                int idx=0;
                for(int k=0; k<9; ++k) {
                    if(k == i || k == j) continue;
                    ans[idx++] = t[k];
                }
                sort(ans, ans+7);
                for(int k=0; k<7; ++k) {
                    printf("%d\n", ans[k]);
                }
                return 0;
            }
        }
    }
}
