#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;

string s;
int n;
vector<int> sfx, g, ng, order;
vector<int> lcp, prevsfx, plcp;
vector<int> cnt(257);

int main()
{
    cin >> s;
    n = s.size();
    sfx.resize(n), g.resize(n+1); ng.resize(n+1); order.resize(n+1, 0);
    for(int i=0; i<n; ++i) {
        sfx[i] = i;
        g[i] = s[i];
    }
    int lim = max(128, n+1);
    for(int t=1; t<n; t<<=1) {
        cnt.clear(); cnt.resize(lim, 0);
        for(int i=0; i<n; ++i) cnt[g[min(i+t,n)]]++;
        for(int i=1; i<lim; ++i) cnt[i] += cnt[i-1];
        for(int i=n-1; i>=0; --i) order[--cnt[g[min(i+t,n)]]] = i;
        cnt.clear(); cnt.resize(lim, 0);
        for(int i=0; i<n; ++i) cnt[g[i]]++;
        for(int i=1; i<lim; ++i) cnt[i] += cnt[i-1];
        for(int i=n-1; i>=0; --i) sfx[--cnt[g[order[i]]]] = order[i];

        auto cmp = [t](int i, int j) -> bool {
            if(g[i] == g[j]) return g[i+t] < g[j+t];
            else return g[i] < g[j];
        };
        
        ng[sfx[0]] = 1;
        for(int i=1; i<n; ++i) ng[sfx[i]] = ng[sfx[i-1]] + (cmp(sfx[i-1], sfx[i]) ? 1 : 0);
        g = ng;
    }
    
    for(int i=0; i<n; ++i) {
        printf("%d ", sfx[i] + 1);
    } putchar('\n');

    lcp.resize(n); prevsfx.resize(n+1); plcp.resize(n+1);
    prevsfx[sfx[0]] = -1;
    for(int i=1; i<n; ++i) prevsfx[sfx[i]] = sfx[i-1];
    for(int i=0, common=0; i<n; ++i) {
        if(prevsfx[i] == -1) plcp[i] = 0;
        else {
            while(s[i+common] == s[prevsfx[i] + common]) ++common;
            plcp[i] = common;
            common = max(common-1, 0);
        }
    }
    for(int i=0; i<n; ++i) lcp[i] = plcp[sfx[i]];
    
    printf("x ");
    for(int i=1; i<n; ++i) {
        printf("%d ", lcp[i]);
    } putchar('\n');
}



