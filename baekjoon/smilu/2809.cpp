/*
 * https://www.acmicpc.net/problem/2809
 * author: smilu97
 */
#include <cstdio>
#include <cstring>
#include <queue>
#include <map>
using namespace std;

// #define DEBUG

int N, M;
char s[300001];
char a[300001];
char p[5001];

struct Node {
    map<int, Node*> children;
    Node* failure;
    int outputSize;
    bool has(int key) {
        return children.find(key) != children.end();
    }
    Node() {
        failure = 0;
        outputSize = 0;
    }
};

Node* root = new Node();
int last_node = 1;

int imax(int a, int b) {
    return a < b ? b : a;
}

void build_links()
{
    queue<Node*> q;
    q.push(root);

    while(!q.empty()) {
        Node* u = q.front();
        q.pop();

        for (auto it = u->children.begin(); it != u->children.end(); ++it) {
            int value = it->first;
            Node* v = it->second;
            Node* p = u;
            while (p != root) {
                if (p->failure->has(value)) {
                    v->failure = p->failure->children[value];
                    break;
                }
                p = p->failure;
            }
            if (p == root) {
                v->failure = root;
            }
            v->outputSize = imax(v->outputSize, v->failure->outputSize);
            q.push(v);
        }
    }
}

int main(void)
{
    scanf("%d%s%d", &N, s, &M);
    for (int i = 0; i < M; i++) {
        scanf("%s", p);
        int pl = strlen(p);
        Node* cur = root;
        char* pc = p;
        while (1) {
            int value = *pc - 'a';
            if (!cur->has(value)) {
                // if (last_node >= NUM_NODE) {
                //     printf("Failed to allocate new node\n");
                //     return 0;
                // }
                Node* newNode = new Node();
                cur->children[value] = newNode;
            }
            cur = cur->children[value];
            ++pc;
            if (*pc == '\0') {
                cur->outputSize = pl;
                break;
            }
        }
    }
#ifdef DEBUG
    printf("Completed to build graph\n");
#endif

    build_links();
    root->failure = root;

#ifdef DEBUG
    for (int i = 0; i < last_node; i++) {
        printf("Node %d:\n", i);
        printf("children: ");
        for (auto it = nodes[i].children.begin(); it != nodes[i].children.end(); ++it) {
            printf("%d(%ld) ", it->second->value, it->second - nodes);
        } puts("");
        printf("failure: %ld\n", nodes[i].failure - nodes);
        printf("outputSize: %d\n", nodes[i].outputSize);
        printf("value: %d\n\n", nodes[i].value);
    }
#endif

    Node* cur = root;
    for (int i = 0; i < N; i++) {
        int value = s[i] - 'a';
        while (cur != root && !cur->has(value)) {
            cur = cur->failure;
        }
        if (cur->has(value)) {
            cur = cur->children[value];
        }
        for (int j = i; j > i - cur->outputSize && j >= 0; --j) {
            a[j] = 1;
        }
    }

    int res = 0;
    for (int i = 0; i < N; i++) {
        if (a[i] == 0) ++res;
    }

    printf("%d", res);

    return 0;
}