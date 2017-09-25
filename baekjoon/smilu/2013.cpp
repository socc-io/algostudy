#include<iostream>
#include<vector>
using namespace std;

typedef long long lld;
typedef lld ptype;

struct position {
    ptype x, y;
    position(){} 
    position(ptype x, ptype y):x(x),y(y) {}
    position operator-(const position &o) const {
        return position(x - o.x, y - o.y);
    }
    ptype operator*(const position &o) const {
        return x*o.y - y*o.x;
    }
    bool operator<(const position &o) const {
        if(x == o.x) return y < o.y;
        return x < o.x;
    }
};

bool parallel(position a, position b) {
    return a*b == 0;
}

struct line {
    position p[2];
    bool operator*(const line &o) const {
        position a = p[1] - p[0];
        position b = o.p[0] - p[0];
        position c = o.p[1] - p[0];
        if( !parallel(a, b) || !parallel(a, c) ) return false;
        ptype ak = a.x + a.y;
        ptype bk = b.x + b.y;
        ptype ck = c.x + c.y;
        if(ak < 0) {
            ak *= -1;
            bk *= -1;
            ck *= -1;
        }
        if(0 <= bk && bk <= ak) return true;
        if(0 <= ck && ck <= ak) return true;
        return false;
    }
    void operator+=(const line &o) {
        if(o.p[0] < p[0]) p[0] = o.p[0];
        if(p[1] < o.p[1]) p[1] = o.p[1];
    }
};

int main()
{
    while(1) {
        int n;
        cin >> n;
        if(n == 0) break;
        vector<line> lines(n);
        for(int i=0; i<n; ++i) {
            double x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            if(1) {
                x1 *= 100, y1 *= 100; 
                x2 *= 100, y2 *= 100;
            }
            lines[i].p[0] = position(x1, y1);
            lines[i].p[1] = position(x2, y2);
            if(lines[i].p[1] < lines[i].p[0]) swap(lines[i].p[0], lines[i].p[1]);
        }
        vector<bool> alive(n, true);
        int dcnt = 0;
        for(int i=0; i<n; ++i) {
            if(!alive[i]) continue;
            for(int j=i+1; j<n; ++j) {
                if(!alive[j]) continue;
                if(lines[i] * lines[j]) {
                    lines[i] += lines[j];
                    alive[j] = false;
                    j = i;
                    ++dcnt;
                }
            }
        }
        printf("%d\n", n-dcnt);
    }
}

