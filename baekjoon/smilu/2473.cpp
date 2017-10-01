#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

typedef long long lld;

vector<lld> a;
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
    lld ans[3], comp;
    ans[0] = -1;
    for(int i=0; i<n; ++i) {
        for(int j=i+1; j<n; ++j) {
            lld t = -(a[i]+a[j]);
            int idx = lower_bound(a.begin(), a.end(), t) - a.begin();
            int r = idx, l = idx-1;
            while(r < n && (r == i || r == j)) ++r;
            if(r < n) {
                if(abs(t-a[r]) < comp || ans[0] == -1) {
                    ans[0] = i, ans[1] = j, ans[2] = r;
                    comp = abs(t-a[r]);
                }
            }
            while(l >= 0 && (l == i || l == j)) --l;
            if(l >= 0) {
                if(abs(t-a[l]) < comp || ans[0] == -1) {
                    ans[0] = i, ans[1] = j, ans[2] = l;
                    comp = abs(t-a[l]);
                }
            }
        }
    }
    ans[0] = a[ans[0]];
    ans[1] = a[ans[1]];
    ans[2] = a[ans[2]];
    sort(ans, ans+3);
    printf("%lld %lld %lld\n", ans[0], ans[1], ans[2]);
}
