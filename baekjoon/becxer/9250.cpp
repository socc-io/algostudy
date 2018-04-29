#include <iostream>
#include <cstring>
#include <queue>

#define MAX_CHAR 26

using namespace std;

char query[101];
char target[10001];

class Node {
public:
  char _A;
  Node* _parent;
  Node* _linkmap[MAX_CHAR];
  Node* _faillink;
  bool _isfinal;
  Node(char _A, Node* init_fail){
    _A = _A; _parent = NULL; _faillink = init_fail; _isfinal = false;
    for(int i = 0; i < MAX_CHAR ; i++) _linkmap[i] = NULL;
  }
};

Node* root = new Node(NULL, NULL);
void struct_trie(char* seq, Node* parent){
  if(seq[0] == NULL) {
    parent->_isfinal = true;
    return;
  }
  int now_char = seq[0] - 'a';
  Node* now_node = parent->_linkmap[now_char];
  if(now_node == NULL){
    now_node = new Node(now_char, root);
    parent->_linkmap[now_char] = now_node;
    now_node->_parent = parent;
  }
  struct_trie(&seq[1], now_node);
}

void link_faillink(){
  queue <Node*> nq;
  nq.push(root);
  while(!nq.empty()){
    Node* now = nq.front(); nq.pop();
    if(now->_parent != NULL && now->_faillink != NULL){
      Node* fail_node = now->_parent->_faillink;
      for(int i = 0; i< MAX_CHAR ; i++){
        if(fail_node->_linkmap[i] != NULL && i == (now->_A - 'a')){
          now->_faillink = fail_node->_linkmap[i];
          break;
        }
      }
    }
    for(int i = 0 ; i < MAX_CHAR ; i++){
      if(now->_linkmap[i] != NULL) nq.push(now->_linkmap[i]);
    }
  }
}

int main(void){
  int count_query = 0;
  int count_target = 0;

  cin >> count_query;
  for(int i =0; i < count_query; i++){
    cin >> query;
    struct_trie(query, root);
  }
  link_faillink();
  cin >> count_target;
  return 0;

  for(int i =0; i < count_target; i++){
    cin >> target;
    int tlen = strlen(target);
    bool found =false;
    Node* now = root;
    for(int j = 0; j < tlen ; j++){
      int tchar = target[j] - 'a';
      if(now->_linkmap[tchar] != NULL){
        now = now->_linkmap[tchar];
      }else{
        now = now->_faillink;
      }
      if(now->_isfinal){
        found = true;
        break;
      }
    }
    if(found) cout << "YES"<< endl;
    else cout <<"No" << endl;
  }
  return 0;
}

