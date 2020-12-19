#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second

typedef pair<int, int> pi;

struct Zipper: vector<int> {
    void organize() { // O(nlgn)
        sort(begin(), end()); // O(nlgn)
        erase(unique(begin(), end()), end()); // O(n)
    }
    int get(int x) { // O(lgn)
        return lower_bound(begin(), end(), x) - begin();
    }
};

int n;
pi ps[10010];
int cs[20020];

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    Zipper zip;
    for (int i = 0; i < n; i++) {
        cin >> ps[i].x >> ps[i].y;
        zip.push_back(ps[i].x);
        zip.push_back(ps[i].y);
    }
    zip.organize();
    for (int i = 0; i < n; i++) {
        ps[i].x = zip.get(ps[i].x);
        ps[i].y = zip.get(ps[i].y);
        for (int j = ps[i].x; j <= ps[i].y; j++) cs[j] = i+1;
    }
    sort(cs, cs+20020);
    int ans = unique(cs, cs+20020) - cs;
    cout << ans-1 << '\n';
}
