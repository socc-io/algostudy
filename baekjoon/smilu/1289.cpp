#include<iostream>
#include<vector>
using namespace std;

#define MOD (1000000007)
typedef unsigned long long llu;

typedef unsigned long long llu;

struct edge {
    int v, w;
    edge(int v, int w):v(v),w(w) {}
};

int n;
vector<edge> edges[100000];
llu res;

llu visit(int pos, int parent)
{
    llu s = 1;
    for(edge e: edges[pos]) {
        if(e.v == parent) continue;
        llu t = visit(e.v, pos) * e.w % MOD;
        res = (res + t*s) % MOD;
        s = (s+t) % MOD;
    }
    return s;
}

int main()
{
    scanf("%d", &n);
    for(int i=0; i<n-1; ++i) {
        int a, b, w;
        scanf("%d%d%d", &a, &b, &w);
        --a; --b;
        edges[a].push_back(edge(b, w));
        edges[b].push_back(edge(a, w));
    }
    visit(0, -1);
    printf("%llu", res);
}

