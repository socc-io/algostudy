#include <iostream>

using namespace std;

int N = 1000; int M = 1000;

class Edge{
public:
  int from; int to; int w; int back_idx;
  Edge(int form, int to, int w, int back_idx)
    : from(from), to(to), w(w), back_idx(back_idx){}
};

class Node{
public:
  bool goal = false;
  Edge* edges[1001];
  int edge_size=0;
  int pushback_edge(Edge* e){
    edges[edge_size++] = e;
  }
};

Node* node_list[2003];

void link_edge(int n1, int n2, int w){
  node_list[n1]->pushback_edge(new Edge(n1, n2, w, node_list[n2]->edge_size));
  node_list[n2]->pushback_edge(new Edge(n2, n1, 0, node_list[n1]->edge_size-1));
}
int debug_count = 0;
int DFS_best_flow(Node* parent, Edge* e, int flow){
  cout << e->from << "->" << e->to << endl;
  if (debug_count > 10) return 0;
  else debug_count++;
  Node* now = node_list[e->to];
  if(now->goal){
    e->w -= flow;
    now->edges[e->back_idx]->w += flow; 
    return flow;
  }else{
    for(int i=0; i < now->edge_size; i++){
      Edge* go_edge = now->edges[i];
      if(go_edge->w > 0){
        flow = (flow < go_edge->w)? flow : go_edge->w;
        flow = DFS_best_flow(now, go_edge, flow);
        if(flow == -1) continue;
        e->w -= flow;
        now->edges[e->back_idx]->w += flow;
        return flow;
      }
    }
    return -1;
  }
}

int FordFulkerson(Node* start){
  int res = 0;
  
  for(int i = 0; i < start->edge_size; i++){
    int one_res = DFS_best_flow(start, start->edges[i], 1);
     if(one_res > 0) res += one_res;
  }
  return res;
}

int main(void){
  int node_count = 0;
  cin >> N >> M;
  for(int i=0; i<N+M+2; i++){
    node_list[node_count++] = new Node();
  }
  node_list[N+M+1]->goal = true;
  
  for(int i=1; i<=N; i++){
    link_edge(0,i,1);
    int work_n; cin >> work_n;
    for(int j=0; j<work_n; j++){
      int work; cin >> work;
      int w = N + work;
      link_edge(i,w,1);
    }
  }
  for(int i=N+1; i<N+M+1; i++){
    link_edge(i,N+M+1,1);
  }
  cout << "good"<< endl;
  cout << FordFulkerson(node_list[0]) << endl;
  return 0;
}
