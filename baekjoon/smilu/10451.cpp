#include<iostream>
#include<vector>
using namespace std;

int arr[1000];
int grp[1000];
int n;

int main()
{
    int T;
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        int grp_idx = 1;
        for(int i=0; i<n; ++i) {
            scanf("%d", arr+i);
            --arr[i];
            grp[i] = -1;
        }
        for(int i=0; i<n; ++i) {
            if(grp[i] != -1) continue;
            int cur = i;
            while(grp[cur] == -1) {
                grp[cur] = i;
                cur = arr[cur];
            }
            if(grp[cur] == i) grp_idx++;
        }
        printf("%d\n", grp_idx-1);
    }
}
