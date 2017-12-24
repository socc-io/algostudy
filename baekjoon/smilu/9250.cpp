#include<iostream>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;

struct node
{
    char ch;
    int fail;
    int success;
    int parent;
    int child[26];
    node(char ch=0, int parent=-1):ch(ch) {
        for(int i=0; i<26; ++i) child[i] = -1;
        fail = -1;
        success = -1;
    }
};

int n, m;
char s[101];
char q[10001];

vector<node> nodes;

int main()
{
    scanf("%d", &n);
    nodes.push_back(node());
    for(int i=0; i<n; ++i) {
        scanf("%s", s);
        int slen = strlen(s);
        int cur = 0;
        for(int j=0; j<slen; ++j) {
            char ch = s[j];
            if(nodes[cur].child[ch-'a'] == -1) {
                nodes[cur].child[ch-'a'] = nodes.size();
                nodes.push_back(node(ch, cur));
            }
            cur = nodes[cur].child[ch-'a'];
        }
        nodes[cur].success = 1;
    }
    queue<int> Q;
    Q.push(0);
    while(!Q.empty()) {
        int u = Q.front(); Q.pop();
        for(int i=0; i<26; ++i) {
            if(nodes[u].child[i] == -1) continue;
            int p = u;
            int q = nodes[u].child[i];
            Q.push(q);
            while(p != 0) {
                int pf = nodes[p].fail;
                if(nodes[pf].child[i] != -1) {
                    nodes[q].fail = nodes[pf].child[i];
                    break;
                }
                p = pf;
            }
            if(nodes[q].fail == -1) {
                nodes[q].fail = 0;
            }
            if(nodes[nodes[q].fail].success != -1) {
                nodes[q].success = 1;
            }
        }
    }
    scanf("%d", &m);
    for(int i=0; i<m; ++i) {
        scanf("%s", q);
        int qlen = strlen(q);
        int cur = 0;
        bool found = false;
        for(int j=0; j<qlen; ++j) {
            char ch = q[j];
            while(cur != -1 && nodes[cur].child[ch-'a'] == -1) cur = nodes[cur].fail;
            if(cur == -1) {
                cur = 0;
                continue;
            }
            cur = nodes[cur].child[ch-'a'];
            if(nodes[cur].success != -1) {
                puts("YES");
                found = true;
                break;
            }
        }
        if(!found) {
            puts("NO");
        }
    }
}


