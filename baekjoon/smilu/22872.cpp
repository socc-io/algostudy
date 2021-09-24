#include <bits/stdc++.h>
using namespace std;

int cost[30];

int main() {
  int n; cin >> n;

  cost[1] = 1;
  cost[2] = 3;
  cost[3] = 5;
  cost[4] = 
  for (int i = 2; i <= 26; i++) {
    cost[i] = (cost[i-1] << 1) | 1;
  }
}
