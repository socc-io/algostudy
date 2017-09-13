#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

#define MAX_SHIP 100000
#define MAX_CANONS 100000
#define MAX_POS 400000

#define INF 1234567890

struct Ship
{
    int x1, x2, y1, y2;
    int w;
    void input() {
        scanf("%d%d%d%d%d", &x1, &y1, &x2, &y2, &w);
        if(x1 > x2) swap(x1, x2);
        if(y1 > y2) swap(y1, y2);
    }
};
struct Canon
{
    int dir, pos;
    int k_ship;
    void input() { scanf("%d%d", &pos, &dir); k_ship = 0; }
};

int n, k, l;
Ship ships[MAX_SHIP];
Canon canons[MAX_CANONS];

vector<int> xpos;
vector<int> ypos;

struct STree
{
    vector<int> tree;
    int first;
    STree(int _size) {
        for(first=1; first<_size; first<<=1);
        tree.resize(_size<<2, INF);
    }
    void update(int pos, int value)
    {
        pos += first;
        tree[pos] = value;
        pos >>= 1;
        while(pos > 0) {
            tree[pos] = min(tree[pos<<1], tree[pos<<1|1]);
            pos >>= 1;
        }
    }
    int query(int left, int right)
    {
        left += first, right += first;
        int res = INF;
        while(left <= right) {
            res = min(res, min(tree[left], tree[right]));
            left = (left+1)>>1;
            right = (right-1)>>1;
        } 
        return res;
    }
};

inline int convertX(int val) { return lower_bound(xpos.begin(), xpos.end(), val) - xpos.begin(); }
inline int convertY(int val) { return lower_bound(ypos.begin(), ypos.end(), val) - ypos.begin(); }

void run()
{
    scanf("%d%d%d", &n, &k, &l);
    xpos.clear(), ypos.clear();
    xpos.reserve(MAX_POS), ypos.reserve(MAX_POS);
    for(int i=0; i<k; ++i) {
        ships[i].input();
        xpos.push_back(ships[i].x1), xpos.push_back(ships[i].x2);
        ypos.push_back(ships[i].y1), ypos.push_back(ships[i].y2);
    }
    for(int i=0; i<l; ++i) {
        canons[i].input();
        if(canons[i].dir) {
            xpos.push_back(canons[i].pos);
        } else {
            ypos.push_back(canons[i].pos);
        }
    }
    sort(xpos.begin(), xpos.end());
    sort(ypos.begin(), ypos.end());
    xpos.erase(unique(xpos.begin(), xpos.end()), xpos.end()); 
    ypos.erase(unique(ypos.begin(), ypos.end()), ypos.end());
    // puts("zipped space");
    STree xtree(xpos.size()), ytree(ypos.size());
    for(int i=0; i<l; ++i) {
        int dir = canons[i].dir, pos = canons[i].pos;
        if(dir) {
            pos = convertX(pos);
            xtree.update(pos, i);
        } else {
            pos = convertY(pos);
            ytree.update(pos, i);
        }
    }
    // puts("updated tree");
    for(int i=0; i<k; ++i) {
        int w = ships[i].w;
        int x1 = convertX(ships[i].x1), x2 = convertX(ships[i].x2);
        int y1 = convertY(ships[i].y1), y2 = convertY(ships[i].y2);
        int xc = xtree.query(x1, x2);
        int yc = ytree.query(y1, y2);
        int c = min(xc, yc);
        if(c != INF) canons[c].k_ship = max(canons[c].k_ship, w);
    }
    for(int i=0; i<l; ++i) {
        printf("%d\n", canons[i].k_ship);
    }
}

int main()
{
    int T; 
    scanf("%d", &T);
    while(T--) {
        // printf("Phase %d Start!\n", T);
        run();
    }
}

