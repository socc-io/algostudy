#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

typedef pair<int,int> pii;

int main()
{
    int n,m;
    scanf("%d%d", &n, &m);
    vector<pii> arr(n);
    for(int i=0; i<n; ++i) {
        scanf("%d", &(arr[i].second));
        arr[i].first = i;
    }
    sort(arr.begin(), arr.end(), [](pii &a, pii &b){ return a.second < b.second; });
    for(int i=0; i<m; ++i) {
        int left, right, k;
        scanf("%d%d%d", &left, &right, &k);
        --left; --right;
        int idx=0;
        for(int j=0; j<n; ++j) {
            if(left <= arr[j].first && arr[j].first <= right) {
                ++idx;
                if(idx == k) {
                    printf("%d\n", arr[j].second);
                    break;
                }
            }
        }
    }
}
