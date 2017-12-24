#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main()
{
    int n, m;
    scanf("%d", &n);
    vector<int> a(n);
    for(int i=0; i<n; ++i) {
        int tmp;
        scanf("%d", &tmp);
        a[i] = tmp;
    }
    sort(a.begin(), a.end());
    scanf("%d", &m); 
    for(int i=0; i<m; ++i) {
        int val;
        scanf("%d", &val);
        int idx = lower_bound(a.begin(), a.end(), val) - a.begin();
        if(a[idx] == n || a[idx] != val) {
            printf("0 ");
        } else {
            printf("1 ");
        }
    }
}
