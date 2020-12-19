#include <bits/stdc++.h>
using namespace std;

struct Paint {
    int c, x1, y1, x2, y2, id;
    void input() {
        cin >> c >> x1 >> y1 >> x2 >> y2;
    }
} ps[100010];
vector<Paint> fs;
int bk[100010];
int ps_idx;
int head;

struct cmp_paint {
    bool operator()(const Paint &a, const Paint &b) {
        return a.id > b.id;
    }
};

struct Node {
    set<int> v[2];
} nd[1<<11];

vector<int> saves;

vector<Paint> in[1010], out[1010];

int n, k, m;

int odd = 1;
int rm(int v) { return (v & 1) ? odd : (1 - odd); }

void invalidate(int n, int s, int e, int f, int t, int id, int odd) {
    if (e < f || s > t) return;
    if (f <= s && e <= t) {
        nd[n].v[rm(f^odd)].erase(id);
    } else {
        int l = n<<1, r = l|1, m = (s+e)>>1;
        invalidate(l,s,m,f,t,id,odd);
        invalidate(r,m+1,e,f,t,id,odd);
    }
}

void insert(int n, int s, int e, int f, int t, int id) {
    if (e < f || s > t) return;
    if (f <= s && e <= t) {
        nd[n].v[rm(f)].insert(id);
    } else {
        int l = n<<1, r = l|1, m = (s+e)>>1;
        insert(l,s,m,f,t,id);
        insert(r,m+1,e,f,t,id);
    }
}

int query(int n, int s, int e, int x) {
    if (e < x || s > x) return -1;
    auto & st = nd[n].v[rm(x)];
    int cur = st.empty() ? -1 : (*st.rbegin());
    if (s == e) return cur;
    int l = n<<1, r = l|1, m = (s+e)>>1;
    if (x <= m) return max(cur, query(l,s,m,x));
    else return max(cur, query(r,m+1,e,x));
}

int query(int x) {
    return query(1,0,1023,x);
}

int color(int id) {
    if (id == -1) return 1;
    return fs[id].c;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n >> k >> m;
    head = -1;
    for (int i = 0; i < m; i++) {
        string cmd; cin >> cmd;
        if (cmd == "PAINT") {
            ps[ps_idx].input();
            bk[ps_idx] = head;
            head = ps_idx;
            ++ps_idx;
        } else if (cmd == "SAVE") {
            saves.push_back(head);
        } else if (cmd == "LOAD") {
            int tmp; cin >> tmp;
            head = saves[tmp - 1];
        }
    }
    while (head >= 0) {
        fs.push_back(ps[head]);
        head = bk[head];
    }
    reverse(fs.begin(), fs.end());
    for (int i = 0; i < fs.size(); i++) {
        auto & p = fs[i];
        p.id = i;
        in[p.x1].push_back(p);
        out[p.x2+1].push_back(p);
    }
    for (int x = 0; x < n; x++) {
        for (int i = 0; i < out[x].size(); i++) {
            Paint & p = out[x][i];
            invalidate(1, 0, 1023, p.y1, p.y2, p.id, p.x2 - p.x1 + 1);
        }
        for (int i = 0; i < in[x].size(); i++) {
            Paint & p = in[x][i];
            insert(1, 0, 1023, p.y1, p.y2, p.id);
        }
        for (int y = 0; y < n; y++) {
            cout << color(query(y)) << ' ';
        }
        cout << '\n';
        odd ^= 1;
    }
}
