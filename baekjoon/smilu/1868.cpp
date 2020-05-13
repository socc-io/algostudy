#include <cstdio>
#include <vector>
using namespace std;

int fastscan() 
{ 
    bool negative = false; 
    int c; 
    int number = 0; 
    c = getchar(); 
    if (c=='-') 
    { 
        negative = true; 
        c = getchar(); 
    } 
    for (; (c>47 && c<58); c=getchar()) 
        number = number *10 + c - 48; 
    if (negative) 
        number *= -1; 
    return number;
} 

const int MAX_N = 50001;

int n;
vector<int> adj[MAX_N];

int biggest_bit(int v) {
  int ret = -1;
  while (v) {
    ++ret;
    v >>= 1;
  }
  return ret;
}

int compute(int u, int p) {
  int r_or = 0, r_two = 0;
  for (int v: adj[u]) {
    if (v == p) continue;
    int sub = compute(v, u);
    r_two |= (r_or & sub);
    r_or |= sub;
  }
  int b = 1 << (biggest_bit(r_two) + 1);
  while (r_or & b) b <<= 1;
  return b | (r_or & (~((b<<1)-1)));
}

int main(void)
{
  n = fastscan();;
  for (int i = 1; i < n; i++) {
    int a = fastscan(); 
    int b = fastscan();
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  int ret = compute(1, 0);
  printf("%d\n", biggest_bit(ret));
}
