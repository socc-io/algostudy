#include <bits/stdc++.h>
using namespace std;

int n, p, q;
char pv, qv;
char s[10010];
char es[10010];
char t[10010];

vector<int> l1_list;
vector<int> l3_list;

void print_vi(vector<int> &vi) {
  putchar('[');
  for (int i = 0; i < ((int)vi.size()) - 1; i++) {
    printf("%d, ", vi[i]);
  }
  if (vi.size() > 0) printf("%d", vi[vi.size()-1]);
  putchar(']');
}

void compose_es() {
  int len = 0;
  for (int i = 0; i < n; i++) {
    if (i == p || i == q) continue;
    es[len++] = s[i];
  }
}

void compose_l1_list() {
  for (int i = 0; i <= n-2; i++) {
    if (t[i] == pv) l1_list.push_back(i);
    if (es[i] != t[i]) break;
  }
}

void compose_l3_list() {
  for (int i = 0; i <= n-2; i++) {
    if (t[n-1-i] == qv) l3_list.push_back(i);
    if (es[n-3-i] != t[n-1-i]) break;
  }
}

bool check_l3(int l3) {
  auto it = lower_bound(l3_list.begin(), l3_list.end(), l3);
  return it != l3_list.end() && *it == l3;
}

bool search_l1_space(int l1) {
  for (int l2 = 0; l2 <= n-2-l1; l2++) {
    const int l3 = n-2-l1-l2;
    if (t[l1+l2+1] == qv && check_l3(l3)) return true;
    if (es[l1+l2] != t[l1+l2+1]) break;
  }
  return false;
}

bool search() {
  for (int l1: l1_list) {
    if (search_l1_space(l1)) return true;
  }
  return false;
}

int main() {
  scanf("%d%s%s%d%d", &n, s, t, &p, &q);
  pv = s[p]; qv = s[q];
  compose_es();
  compose_l1_list();
  compose_l3_list();

  // printf("s:  %s\n", s);
  // printf("es: %s\n", es);
  // printf("t:  %s\n", t);
  // printf("l1_list: "); print_vi(l1_list); puts("");
  // printf("l3_list: "); print_vi(l3_list); puts("");

  puts(search() ? "YES" : "NO");
}
