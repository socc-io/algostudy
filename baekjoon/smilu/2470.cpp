#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

vector<int> a;
int n;

int main()
{
    scanf("%d", &n);
    a.reserve(n);
    for(int i=0; i<n; ++i) {
        int tmp;
        scanf("%d", &tmp);
        a.push_back(tmp);
    }
    sort(a.begin(), a.end());
    int ans1 = -1, ans2 = -1;
    int c;
    for(int i=0; i<n; ++i) {
        int t = -a[i];
        int idx = lower_bound(a.begin(), a.end(), t) - a.begin();
        if(idx != n && idx != i) {
            if(abs(a[i]+a[idx]) < c || ans1 == -1) {
                ans1 = i;
                ans2 = idx;
                c = abs(a[i]+a[idx]);
            }
        }
        --idx;
        if(idx >= 0 && idx != i) {
            if(abs(a[i]+a[idx]) < c || ans1 == -1) {
                ans1 = i;
                ans2 = idx;
                c = abs(a[i]+a[idx]);
            }
        }
    }
    ans1 = a[ans1];
    ans2 = a[ans2];
    if(ans1>ans2) swap(ans1,ans2);
    printf("%d %d\n", ans1, ans2);
}
   
