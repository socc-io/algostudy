#include <iostream>

using namespace std;

struct node {
  int start[3];
  int end[3];
  int child_sum[3];
  int my_sum;
  node* child[3];
} node;


node* build_seg_tree(int start, int end){
  if(start == end){
    
  }
}
