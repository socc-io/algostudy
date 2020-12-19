#include <bits/stdc++.h>
using namespace std;

#define LEFT(x) (x<<1)
#define RIGHT(x) ((x<<1)|1)

const int SZ = 1<<18;
const int HSZ = 1<<17;

int v[SZ];
int n, m;

int query(int n, int s, int e, int f, int t) {
    if (e < f || t < s) return 0x3f3f3f3f;
    if (f <= s && e <= t) return v[n];
    int l = (n<<1), r = l|1, m = (s+e)>>1;
    return min(query(l,s,m,f,t), query(r,m+1,e,f,t));
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m;
    for (int i = 0; i < n; i++) cin >> v[HSZ+i];
    for (int i = HSZ-1; i >= 1; i--) v[i] = min(v[LEFT(i)], v[RIGHT(i)]);
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        cout << query(1,1,HSZ,a,b) << '\n';
    }
}
