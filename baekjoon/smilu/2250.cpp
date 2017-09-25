#include<iostream>
using namespace std;

#define INF 1234567890

struct node
{
    int left, right;
    int level;
    int parent;
};

node nodes[10000];
int n;
int xidx;
int max_level;
int level_minx[10000];
int level_maxx[10000];

void visit(int pos)
{
    int level = nodes[pos].level;
    int next_level = level + 1;
    if(next_level > max_level) max_level = next_level;
    if(nodes[pos].left >= 0) {
        nodes[nodes[pos].left].level = next_level;
        visit(nodes[pos].left);
    }
    level_minx[level] = min(level_minx[level], xidx);
    level_maxx[level] = max(level_maxx[level], xidx);
    ++xidx;
    if(nodes[pos].right >= 0) {
        nodes[nodes[pos].right].level = next_level;
        visit(nodes[pos].right);
    }
}

int main()
{
    scanf("%d", &n);
    for(int i=0; i<n; ++i) {
        nodes[i].parent = -1;
    }
    for(int i=0; i<n; ++i) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        --a; --b; --c;
        nodes[a].left = b;
        nodes[a].right = c;
        if(b >= 0) nodes[b].parent = a;
        if(c >= 0) nodes[c].parent = a;
    }
    int root;
    for(int i=0; i<n; ++i) {
        if(nodes[i].parent == -1) {
            root = i;
            break;
        }
    }
    for(int i=0; i<10000; ++i) {
        level_minx[i] = INF;
        level_maxx[i] = -1;
    }
    visit(root);
    int max_width = -1;
    int max_width_idx = -1;
    for(int i=0; i<max_level; ++i) {
        int width = level_maxx[i] - level_minx[i] + 1;
        if(max_width < width) {
            max_width = width;
            max_width_idx = i;
        }
    }
    printf("%d %d\n", max_width_idx+1, max_width);
}

