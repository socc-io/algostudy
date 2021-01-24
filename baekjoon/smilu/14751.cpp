#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p;

#define INF 0x7fffffffffffffff

ll gcd(ll a, ll b) {
    if (a < b) swap(a, b);
    while (b) {
        ll tmp = a % b;
        a = b;
        b = tmp;
    }
    return a;
}

struct CHT{ // max cht
	ll a[101010], b[101010], c[101010];
	int pv, top;

	void clear(){
		pv = top = 0;
	}

	ll f(ll idx, ll x){
		return a[idx]*x + b[idx];
	}

	void insert(ll aa, ll bb, ll cc){
		if(top >= 1 && aa == a[top-1]){
			c[top-1] = cc; return;
		}
		while(top >= 2 && (b[top-1] - b[top-2]) * (a[top-2] - aa) >= (bb - b[top-2]) * (a[top-2] - a[top-1])) top--;
		a[top] = aa;
		b[top] = bb;
		c[top] = cc;
		top++;
		if(pv >= top) pv = top - 1;
	}

	p query(ll x){
		while(pv+1 < top && a[pv+1]*x + b[pv+1] > a[pv]*x + b[pv]) pv++;
		return {f(pv, x), c[pv]};
	}
} lc;

ll max_y, min_y;
double mult;
int n, m;

pair<ll,ll> lines[100010];

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> max_y >> min_y >> n;
    double dy = max_y - min_y;
    mult = 1000 * dy / gcd(1000, dy);

    for (int i = 0; i < n; i++) {
        double a, b;
        cin >> a >> b;
        a *= mult;
        b *= mult;

        double k = (a-b)/dy;
        double m = -a;
        lines[i] = {round(k), round(m)};
    }
    sort(lines, lines + n);

    for (int i = 0; i < n; i++) {
        lc.insert(lines[i].first, lines[i].second, i+1);
    }

    // printf("p: "); for (int i = 0; i < lc.top; i++) printf("%lf ", lc.p); puts("");

    cin >> m;
    for (int i = 0; i < m; i++) {
        double y; cin >> y;
        y *= mult;
        cout << lc.query(y).second << '\n';
    }
}
