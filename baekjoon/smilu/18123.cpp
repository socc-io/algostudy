#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct BitString {
  ll value;
  int len;
  BitString operator+(const BitString &o) const {
    BitString ret;
    ret.value = (value << o.len) | o.value;
    ret.len = len + o.len;
    return ret;
  }
  bool operator<(const BitString &bs) const {
    if (value != bs.value) return value < bs.value;
    return len < bs.len;
  }
  bool operator==(const BitString &bs) const {
    return value == bs.value && len == bs.len;
  }
};

const BitString bs_one = {1, 1};
const BitString bs_zero = {0, 1};

int t, n;
vector<int> adj[31];
int sz[31];

void find_centroids(vector<int> &cont, int u, int p = -1) {
  sz[u] = 1;
  bool flag = false;
  for (int v: adj[u]) {
    if (v == p) continue;
    find_centroids(cont, v, u);
    sz[u] += sz[v];
    if (sz[v] > n/2) { flag = true; break; }
  }
  if (n - sz[u] > n/2) flag = true;
  if (!flag) cont.push_back(u);
}

BitString hash_tree(int u, int p = -1) {
  vector<BitString> chs;
  for (int v: adj[u]) {
    if (v == p) continue;
    chs.push_back(hash_tree(v, u));
  }
  sort(chs.begin(), chs.end());
  BitString ret = bs_one;
  for (const auto &ch: chs) {
    ret = ret + ch;
  }
  return ret + bs_zero;
}

int main(void)
{
  vector<BitString> hashes;
  scanf("%d", &t);
  while (t--) {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
      adj[i].clear();
    }
    for (int i = 1; i < n; i++) {
      int a, b; scanf("%d%d", &a, &b);
      adj[a].push_back(b);
      adj[b].push_back(a);
    }
    vector<int> centroids;
    BitString hash = {0, 0};
    find_centroids(centroids, 0);
    for (int cent: centroids) {
      hash = max(hash, hash_tree(cent));
    }
    hashes.push_back(hash);
  }
  sort(hashes.begin(), hashes.end());
  auto hash_end = unique(hashes.begin(), hashes.end());
  printf("%lu\n", distance(hashes.begin(), hash_end));
}
