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