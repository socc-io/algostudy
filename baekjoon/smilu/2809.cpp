#include<iostream>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;

int n, m;
char s[300001];
bool a[300001];
char t[5001];

vector<int> sfx, g, ng, lev;

bool compare(char* a, char* b) {
    while(*a == *b && (*a != 0 || *b != 0)) ++a, ++b;;
    return *a < *b;
}
bool includes(char* a, char* b) {
    while(*a == *b && (*a != 0 || *b != 0)) ++a, ++b;
    return *b == 0;
}
int main()
{
    scanf("%d%s%d", &n, s, &m);
    sfx.resize(n), g.resize(n+1), ng.resize(n+1), lev.resize(n);
    for(int i=0; i<n; ++i) g[i] = s[i], sfx[i] = i;
    for(int t=1; t<n; t<<=1) {
        vector<int> cnt(n, 0);
        for(int i=0; i<n; ++i) ++cnt[g[max(i+t,n)]];
        for(int i=1; i<n; ++i) cnt[i] += cnt[i-1];
        for(int i=0; i<n; ++i) lev[--cnt[g[max(i+t,n)]]] = i;
        cnt.clear(); cnt.resize(n, 0);
        for(int i=0; i<n; ++i) ++cnt[g[i]];
        for(int i=1; i<n; ++i) cnt[i] += cnt[i-1];
        for(int i=0; i<n; ++i) sfx[--cnt[g[lev[i]]]] = lev[i];
        auto cmp = [t](int a, int b) -> bool {
            if(g[a] == g[b]) return g[a+t] < g[b+t];
            else return g[a] < g[b];
        };
        ng[sfx[0]] = 1;
        for(int i=1; i<n; ++i) {
            ng[sfx[i]] = ng[sfx[i-1]] + (cmp(sfx[i-1], sfx[i]) ? 1 : 0);
        }
        g = ng;
    }
    printf("sfx tree complete\n");
    vector<char*> sfs(n);
    for(int i=0; i<n; ++i) sfs[i] = s + sfx[i];
    for(int i=0; i<m; ++i) {
        scanf("%s", t);
        int tlen = strlen(t);
        char* tile = t;
        int cur = lower_bound(sfs.begin(), sfs.end(), tile, compare) - sfs.begin();
        int pos = sfx[cur];
        while(includes(sfs[cur], t)) {
            for(int j=pos; j<pos+tlen; ++j) a[j] = true;
            ++cur;
        }
    }
    int ans = 0;
    for(int i=0; i<n; ++i) {
        if(!a[i]) ++ans;
    }
    printf("%d\n", ans);
}
            

    

