#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

int n, nn;
int arr[200000];
int nxt[200000];
int prv[200000];
int head[200000];
int zip[200000];

inline bool unique_range(int i, int s, int e) {
  return (nxt[i] == i || nxt[i] > e) && (prv[i] == i || prv[i] < s);
}

int find_unique(int s, int e) {
  int sz = (e-s)>>1;
  for (int i = 0; i <= sz; i++) {
    if (unique_range(s+i,s,e)) return s+i;
    if (unique_range(e-i,s,e)) return e-i;
  }
  return e+1;
}

bool check(int s, int e) {
  if (s > e) return true;
  int k = find_unique(s,e);
  if (k > e) return false;
  return check(s,k-1) && check(k+1,e);
}

void solve() {
  scanf("%d", &n);
  for (int i = 0; i < n; i++) scanf("%d", &arr[i]);
  memcpy(zip, arr, sizeof(int)*n);
  sort(zip, zip+n);
  auto ze = unique(zip, zip+n);
  nn = ze - zip;
  for (int i = 0; i < n; i++) arr[i] = lower_bound(zip, ze, arr[i]) - zip;
  for (int i = 0; i < n; i++) head[i] = -1;
  for (int i = n-1; i >= 0; i--) {
    if (head[arr[i]] == -1) {
      head[arr[i]] = i;
      nxt[i] = i;
    } else {
      nxt[i] = head[arr[i]];
      head[arr[i]] = i;
    }
  }
  for (int i = 0; i < n; i++) head[i] = -1;
  for (int i = 0; i < n; i++) {
    if (head[arr[i]] == -1) {
      head[arr[i]] = i;
      prv[i] = i;
    } else {
      prv[i] = head[arr[i]];
      head[arr[i]] = i;
    }
  }
  puts(check(0,n-1) ? "non-boring" : "boring");
}

int main(void)
{
  int t; scanf("%d", &t);
  while (t--) solve();
}
