/*
 * author: smilu97
 * description:
 *   algorithm solving: https://www.welcomekakao.com/learn/courses/30/lessons/42892
 */

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

#define INF 100001

struct Node {
    int id;
    int x;
    int y;
    int begin;
    int end;
    Node* left;
    Node* right;
    void* level;
    Node() { left = 0; right = 0; }
    Node(int id, int x, int y): id(id), x(x), y(y) {
        left = 0;
        right = 0;
    }
};

struct Level {
    int y;
    vector<Node*> nodes;
    Level* next_level;
    Level() {}
    Level(int y): y(y) { next_level = 0; }
};

void preorder(Node* node, vector<int> &vec) {
    vec.push_back(node->id);
    if (node->left) preorder(node->left, vec);
    if (node->right) preorder(node->right, vec);
}

void postorder(Node* node, vector<int> &vec) {
    if (node->left) postorder(node->left, vec);
    if (node->right) postorder(node->right, vec);
    vec.push_back(node->id);
}

vector<vector<int>> solution(vector<vector<int>> nodeinfo) {
    vector<vector<int>> answer;

    int len = nodeinfo.size();
    vector<Node*> nodes;
    vector<Level*> levels;

    /*
     * Build nodes
     */
    int i = 0;
    for (auto node: nodeinfo) {
        nodes.push_back(new Node(++i, node[0], node[1]));
    }
    auto compare = [](Node* a, Node* b) {
        if (a->y == b->y) return a->x < b->x;
        return a->y > b->y;
    };
    sort(nodes.begin(), nodes.end(), compare);

    /*
     * Build level structure
     */
    Level* curr_level = new Level(nodes[0]->y);
    for (auto node: nodes) {
        if (curr_level->y != node->y) {
            Level* old_level = curr_level;
            levels.push_back(old_level);
            curr_level = new Level(node->y);
            old_level->next_level = curr_level;
        }
        curr_level->nodes.push_back(node);
        node->level = (void*) curr_level;
    }
    levels.push_back(curr_level);

    /*
     * Find children
     */
    nodes[0]->begin = -INF;  // Set range of first_node INFINITELY
    nodes[0]->end = INF;
    int child_cur = 1;
    Node* tmp_node = new Node(-1, 0, 0);
    for (auto node: nodes) {
        Level* level = (Level*) node->level;
        Level* nlevel = level->next_level;
        if (nlevel == 0) break;
        tmp_node->x = node->begin;
        tmp_node->y = nlevel->y;
        auto it = lower_bound(nlevel->nodes.begin(), nlevel->nodes.end(), tmp_node, compare);
        for (; it != nlevel->nodes.end() && (*it)->x < node->end; it++) {
            Node* child = *it;
            if (child->x < node->x) {
                node->left = child;
                child->begin = node->begin;
                child->end = node->x;
            } else {
                node->right = child;
                child->begin = node->x;
                child->end = node->end;
            }
        }
    }

    vector<int> pre;
    vector<int> post;
    preorder(nodes[0], pre);
    postorder(nodes[0], post);
    answer.push_back(pre);
    answer.push_back(post);

    return answer;
}
