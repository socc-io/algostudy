#include <iostream>
#include <map>
#include <vector>
using namespace std;

int N,P,C,A, sell_item, sell_count;
int ItemBuy[501];
int ItemCost[501];
map<int, int> map_cost; // <buy , cost>
vector<int> exist_buy; // exist buy
int max_cost = 0;

int main(void){
  cin >> C;
  cin >> N >> P;
  for(int i = 0 ; i < N ; i++){
    cin >> ItemBuy[i] >> ItemCost[i];
    ItemCost[i] -= ItemBuy[i];
  }
  map_cost[0] = 0;
  exist_buy.push_back(0);  
  for(int i = 0 ; i < P ; i++){
    cin >> A;
    int a_buy = 0;
    int a_cost = 0;
    for(int j = 0; j < A ; j++){
      cin >> sell_item >> sell_count;
      a_buy += ItemBuy[sell_item-1] * sell_count;
      a_cost += ItemCost[sell_item-1] * sell_count;
    }
    cout << i+1 << " : " << a_buy << "," << a_cost << endl;
    int v_size = exist_buy.size();
    for(int j = 0; j < v_size ; j++){
      int n_buy = exist_buy[j] + a_buy;
      int n_cost = map_cost[exist_buy[j]] + a_cost;
      if(n_buy <= C){
        if(max_cost < n_cost) {
          max_cost = n_cost;
          cout << "nbuy : " << n_buy << ", n_cost : " << n_cost << endl;
        }
        if(map_cost.count(n_buy)){
          map_cost[n_buy] = (map_cost[n_buy] > n_cost)? map_cost[n_buy] : n_cost;
        }else{
          map_cost[n_buy] = n_cost;
          exist_buy.push_back(n_buy);
        }
      }
    }
  }
  cout << max_cost << endl;
  return 0;
}
