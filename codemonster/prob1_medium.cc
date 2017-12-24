#include<iostream>
#include<algorithm>
using namespace std;

int n;
int a;
pair<int, int> b[100000];

void do_task()
{
    scanf("%d", &n);
    for(int i=0; i<n; ++i) {
        scanf("%d%d", &a, &b[i].first);
        b[i].second = i;
    }
    sort(b, b+n, [](const pair<int,int> &a, const pair<int,int> &b) -> bool {
        if(a.first == b.first) return a.second > b.second;
        else return a.first > b.first;
    });
    long long ans = 0;
    for(long long i=0; i<n; ++i) {
        ans += (i+1) * (b[i].second + 1);
    }
    printf("%lld\n", ans);
}

int main()
{
    int T;
    scanf("%d", &T);
    while(T--) do_task();
}
