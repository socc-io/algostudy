#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <string>
using namespace std;

typedef unsigned long long llu;

// #define DEBUG_PRINT

enum t_edge_op { EDGE_OP_EQ = 1, EDGE_OP_NEQ = -1 };

char S[1000000];
int S_len;
char R[1000000];
int R_len;

set<llu> applied_neq;

struct Node {
    int id;
    char* name;
    int name_len;
    int flag;
    Node* parent;
    Node(char* name, int name_len, int id):
        name(name), name_len(name_len), id(id) {
        this->parent = this;
        this->flag = 0;
    }
};

struct Edge {
    Node* u;
    Node* v;
    Edge(Node* u, Node* v):
        u(u), v(v) {}
};

vector<Node*> nodes;
vector<Edge*> edges; 
vector<char*> S_blocks;
map<string, Node*> node_name_map;

Node* get_most_parent(Node* node)
{
    if (node == node->parent) return node;
    Node* res = get_most_parent(node->parent);
    node->parent = res;
    return res;
}

Node* get_node(char* name)
{
    // Find duplication
    string s_name = string(name);
    auto fr = node_name_map.find(s_name);
    if (fr != node_name_map.end()) {
        return fr->second;
    }

    int name_len = strlen(name);
    Node* node = new Node(
        name,
        name_len,
        nodes.size()
    );
    nodes.push_back(node);
    node_name_map[s_name] = node;

    if ('0' <= name[0] && name[0] <= '9') {
        node->flag = 1;
    } else if (name[0] == '-') {
        node->flag = 1;
    }

    #ifdef DEBUG_PRINT
        printf("New Node %s\n", name);
    #endif

    return node;
}

void make_tree_with_block(char* str)
{
    int op_idx;
    t_edge_op edge_op;
    int len = strlen(str);
    Node* tmp_node;

    // Find != or ==
    for (op_idx = 0; op_idx < len; ++op_idx) {
        if (str[op_idx] == '=') {
            edge_op = EDGE_OP_EQ;
            break;
        } else if (str[op_idx] == '!') {
            edge_op = EDGE_OP_NEQ;
            break;
        }
    }
    str[op_idx] = '\0';

    Node* left_node = get_node(str);
    Node* right_node = get_node(str + (op_idx + 2));

    if (left_node->name_len > right_node->name_len) {
        tmp_node = left_node;
        left_node = right_node;
        right_node = tmp_node;
    }

    if (edge_op == EDGE_OP_EQ) {
        Node* lmp = get_most_parent(left_node);
        Node* rmp = get_most_parent(right_node);
        if (lmp->name_len > rmp->name_len) {
            tmp_node = lmp;
            lmp = rmp;
            rmp = tmp_node;
        }
        rmp->parent = lmp;
    } else {
        Edge* e = new Edge(
            left_node,
            right_node
        );
        edges.push_back(e);
    }

    #ifdef DEBUG_PRINT
        printf("New Edge %s <-> %s\n", left_node->name, right_node->name);
    #endif
}

int apply_eq(Node* node)
{
    Node* parent = get_most_parent(node);
    if (parent == node) return 0;

    if (node->flag == 1) {
        if (parent->flag == 1) return -1;
        parent->flag = 1;
    }

    if (R_len != 0) {
        strcat(R + R_len, "&&");
        R_len += 2;
    }

    strcat(R + R_len, parent->name);
    R_len += parent->name_len;
    strcat(R + R_len, "==");
    R_len += 2;
    strcat(R + R_len, node->name);
    R_len += node->name_len;

    return 0;
}

int apply_neq(Edge* e)
{
    Node* u = e->u;
    Node* v = e->v;
    
    Node* ump = get_most_parent(u);
    Node* vmp = get_most_parent(v);

    if (ump == vmp) return -1;

    llu key = ((llu)ump->id << 32) | vmp->id;
    if (applied_neq.find(key) == applied_neq.end()) {
        applied_neq.insert(key);
    } else return 0;

    if (R_len != 0) {
        strcat(R + R_len, "&&");
        R_len += 2;
    }

    strcat(R + R_len, ump->name);
    R_len += ump->name_len;
    strcat(R + R_len, "!=");
    R_len += 2;
    strcat(R + R_len, vmp->name);
    R_len += vmp->name_len;

    return 0;
}

int main(void)
{
    scanf("%s", S);
    S_len = strlen(S);

    #ifdef DEBUG_PRINT
        printf("S: %s\n", S);
    #endif

    // Split with &&
    S_blocks.push_back(S);
    for (int i = 0; i < S_len; i++) {
        if (S[i] == '&') {
            S[i] = '\0';
            ++i;
            S_blocks.push_back(S + (i + 1));
        }
    }
    for (auto it = S_blocks.begin(); it != S_blocks.end(); ++it) {
        make_tree_with_block(*it);
    }
    for (auto it = nodes.begin(); it != nodes.end(); ++it) {
        if (apply_eq(*it)) {
            printf("0==1\n");
            return 0;
        }
    }
    for (auto it = edges.begin(); it != edges.end(); ++it) {
        if (apply_neq(*it)) {
            printf("0==1\n");
            return 0;
        }
    }

    if (R_len == 0) {
        printf("0==0\n");
    } else {
        printf("%s\n", R);
    }

    return 0;
}
