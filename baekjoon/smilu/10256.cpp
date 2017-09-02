#include <iostream>
#include <queue>

using namespace std;

#define DNA_MAX 1000000
#define MARKER_MAX 100
#define NODE_MAX 1000000

inline int convertDNAToNum(char ch) {
    if(ch == 'A') return 0;
    if(ch == 'C') return 1;
    if(ch == 'G') return 2;
    return 3;
}

int dna_len, marker_len;
int dna[DNA_MAX];
int marker[MARKER_MAX];

int link[NODE_MAX][4];
int fail_link[NODE_MAX];
int succ_link[NODE_MAX];
int link_idx;

inline void register_link()
{
    int cur = 0;
    for(int i=0; i<marker_len; ++i) {
        if(link[cur][marker[i]] == -1) {
            link[cur][marker[i]] = link_idx++;
        }
        cur = link[cur][marker[i]];
    }
    succ_link[cur] = 1;
}
inline void register_fail(int p, int q, int v)
{
    while(1) {
        if(p == 0) { 
            fail_link[q] = 0;
            break;
        }
        int r = link[fail_link[p]][v];
        if(r == -1) {
            p = fail_link[p];
        } else {
            fail_link[q] = r;
            break;;
        }
    }
    int succ_cnt = 0, cur = q;
    while(cur != 0) {
        if(succ_link[cur]) ++succ_cnt;
        cur = fail_link[cur];
    }
    succ_link[q] = succ_cnt;
}
inline void reverse_marker(int from, int to)
{
    while(from < to) {
        int tmp = marker[from];
        marker[from] = marker[to];
        marker[to] = tmp;
        ++from; --to;
    }
}
int main(void)
{
    int T;
    scanf("%d", &T); 
    while(T--) {
        // get input
        scanf("%d%d", &dna_len, &marker_len);
        getchar();
        for(int i=0; i<dna_len; ++i) {
            dna[i] = convertDNAToNum(getchar());
        }
        getchar();
        for(int i=0; i<marker_len; ++i) {
            marker[i] = convertDNAToNum(getchar());
        }
        // build link
        for(int i=0; i<NODE_MAX; ++i) for(int j=0; j<4; ++j) link[i][j] = -1;
        for(int i=0; i<NODE_MAX; ++i) fail_link[i] = -1;
        for(int i=0; i<NODE_MAX; ++i) succ_link[i] = 0;
        link_idx = 1;
        register_link();
        for(int i=0; i<marker_len; ++i) {
            for(int j=i+1; j<marker_len; ++j) {
                reverse_marker(i, j);
                register_link();
                reverse_marker(i, j);
            }
        }
        // build fail link
        queue<int> Q;
        Q.push(0);
        while(!Q.empty()) {
            int p = Q.front(); Q.pop();
            for(int v=0; v<4; ++v) {
                int q = link[p][v];
                if(q == -1) continue;
                register_fail(p, q, v);
                Q.push(q);
            }
        }
        // count pattern 
        int cur = 0, v = -1, cnt = 0;
        for(int i=0; i<dna_len; ++i) {
            while(link[cur][dna[i]] == -1) {
                if(cur == 0) break;
                cur = fail_link[cur];
            }
            if(link[cur][dna[i]] == -1) continue;
            cur = link[cur][dna[i]];
            cnt += succ_link[cur];
        }
        printf("%d\n", cnt);
    }
}
