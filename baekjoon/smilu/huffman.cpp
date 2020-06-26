#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <deque>
#include <cstdint>
#include <algorithm>
using namespace std;

class BitStack {
  vector<uint8_t> batches;
  deque<bool> bits;
public:
  void flush_bits() {
    if (bits.size() < 8) return;
    uint8_t batch = 0;
    for (int i = 7; i >= 0; i--) {
      batch |= bits.front() << i;
      bits.pop_front();
    }
    batches.push_back(batch);
  }
  void push(bool v) {
    bits.push_back(v);
    flush_bits();
  }
  uint size() const {
    return batches.size() + (!bits.empty());
  }
  uint bitsize() const {
    return (batches.size() << 3) | bits.size();
  }
  bool at(uint index) const {
    uint x = index >> 3;
    uint y = index & 7;
    if (x >= batches.size()) {
      if (y >= bits.size()) return false;
      return bits[y];
    }
    return (batches[x] >> (7-y)) & 1;
  }
};

template <class T>
class Huffman {
public:
  struct Node {
    uint32_t weight;
    T rep;
    Node *parent;
    Node *left;
    Node *right;
    void free_children() {
      if (left) {
        left->free_children();
        delete left; left = NULL;
      }
      if (right) {
        right->free_children();
        delete right; right = NULL;  
      }
    }
    bool is_leaf() {
      return left == NULL && right == NULL;
    }
    Node(uint32_t weight, T rep, Node* parent, Node *left, Node *right):
      weight(weight), rep(rep), parent(parent), left(left), right(right) {}
  };
  struct PNode {
    Node *p_node;
    T rep;
    bool is_leaf;
    bool operator<(const PNode &o) const {
      if (p_node->weight != o.p_node->weight)
        return p_node->weight > o.p_node->weight;
      return rep < o.rep;
    }
    PNode(Node *p_node, T rep, bool is_leaf): p_node(p_node), rep(rep), is_leaf(is_leaf) {}
  };
  class Tree: public map<T, Node*> {
    Node *root;

    void _initialize_with_counter(const map<T, uint32_t> &counter) {
      priority_queue<PNode> pq;
      for (auto it = counter.begin(); it != counter.end(); it++) {
        Node *p_node = new Node(it->second, it->first, NULL, NULL, NULL);
        pq.push(PNode(p_node, it->first, true));
        this->insert({it->first, p_node});
      }
      if (pq.size() == 1) {
        Node *chd = pq.top().p_node;
        root = new Node(chd->weight, 0, NULL, chd, NULL);
        chd->parent = root;
        return;
      }
      while (pq.size() > 1) {
        Node *left  = pq.top().p_node; pq.pop();
        Node *right = pq.top().p_node; pq.pop();
        Node *parent = new Node(left->weight + right->weight, 0, NULL, left, right);
        left->parent = parent; right->parent = parent;
        pq.push(PNode(parent, 0, false));
      }
      root = pq.top().p_node;
    }
    vector<bool> _track(const T &v) {
      vector<bool> ret;
      Node * cur = this->find(v)->second;
      while (cur->parent) {
        Node *par = cur->parent;
        ret.push_back(par->left == cur);
        cur = par;
      }
      reverse(ret.begin(), ret.end());
      return ret;
    }
  public:
    Tree(const vector<T> &arr) {
      map<T, uint32_t> counter;
      for (const T &v: arr) counter[v] += 1;
      _initialize_with_counter(counter);
    }
    Tree(const map<T, uint32_t> &counter) {
      _initialize_with_counter(counter);
    }
    ~Tree() {
      root->free_children();
      delete root;
    }
    BitStack encode(const vector<T> &arr) {
      BitStack bs;
      for (const T &v: arr) {
        vector<bool> trk = _track(v);
        for (bool vb: trk) bs.push(vb);
      }
      return bs;
    }
    vector<T> decode(const BitStack &bs) {
      Node* cur = root;
      vector<T> ret;
      for (int i = 0; i < bs.bitsize(); i++) {
        cur = bs.at(i) ? cur->left : cur->right;
        if (cur->is_leaf()) {
          ret.push_back(cur->rep);
          cur = root;
        }
      }
      return ret;
    }
  };
};

int main() {
  string str_test = "abcdefasdfasdfasdf";
  vector<char> vc_test(str_test.begin(), str_test.end());
  auto tree = Huffman<char>::Tree(vc_test);
  BitStack encoded = tree.encode(vc_test);
  vector<char> decoded = tree.decode(encoded);
  string str_decoded(decoded.begin(), decoded.end());
  
  cout << "original size: " << str_test.size() << '\n';
  cout << "encoded size: " << encoded.size() << '\n';
  cout << "compare str_test == str_decoded: " << (str_test == str_decoded) << '\n';
  cout << "str_decoded: " << str_decoded << '\n';
}
