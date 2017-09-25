#include<iostream>
#include<string>
#include<vector>
using namespace std;

int main()
{
    string s;
    cin >> s;
    int n = s.size(), ans = 0, len = 0;
    vector<int> sfx(n), g(n+1), ng(n+1), order(n+1, 0), cnt, rank(n+1, 0);
    for(int i=0; i<n; ++i) sfx[i] = i, g[i] = s[i];
    int lim = max(256, n);
    for(int t=1; t<=n; t<<=1) {
        cnt.clear(); cnt.resize(lim, 0);
        for(int i=0; i<n; ++i) cnt[g[min(i+t,n)]]++;
        for(int i=1; i<lim; ++i) cnt[i] += cnt[i-1];
        for(int i=n-1; i>=0; --i) order[--cnt[g[min(i+t,n)]]] = i;
        cnt.clear(); cnt.resize(lim, 0);
        for(int i=0; i<n; ++i) cnt[g[i]]++;
        for(int i=1; i<lim; ++i) cnt[i] += cnt[i-1];
        for(int i=n-1; i>=0; --i) sfx[--cnt[g[order[i]]]] = order[i];
        ng[sfx[0]] = 1;
        for(int i=1; i<n; ++i) ng[sfx[i]] = ng[sfx[i-1]] + (g[sfx[i-1]] == g[sfx[i]] ? g[sfx[i-1]+t] < g[sfx[i]+t] : g[sfx[i-1]] < g[sfx[i]]);
        g = ng;
    }
    for(int i=0; i<n; ++i) rank[sfx[i]] = i;
    for(int i=0; i<n; ++i) {
        if(rank[i]) {
            int j = sfx[rank[i]-1];
            while(s[i+len] == s[j+len]) ++len;
            ans += len;
        }
        if(len) --len;
    }
    printf("%d", (n*n+n)/2 - ans);
}


