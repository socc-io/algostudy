template<class T> // reads adjacency matrix of the graph
pair<T, vector<int>> hungarian_min_cost_bipartite_matching(const vector<vector<T>> &adjm){
    if(adjm.empty()) return {0, {}};
    int n = (int)adjm.size() + 1, m = (int)adjm[0].size() + 1;
    vector<T> u(n), v(m);
    vector<int> p(m), res(n - 1, -1);
    for(int i = 1; i < n; ++ i){
     p[0] = i;
     int j0 = 0; // add "dummy" worker 0
     vector<T> dist(m, numeric_limits<T>::max());
     vector<int> pre(m, -1);
     vector<bool> done(m + 1);
     do{// dijkstra
         done[j0] = true;
         int i0 = p[j0], j1;
         long long delta = numeric_limits<long long>::max();
         for(int j = 1; j < m; ++ j) if(!done[j]){
             auto cur = adjm[i0 - 1][j - 1] - u[i0] - v[j];
             if(cur < dist[j]) dist[j] = cur, pre[j] = j0;
             if(dist[j] < delta) delta = dist[j], j1 = j;
         }
         for(int j = 0; j < m; ++ j){
             if(done[j]) u[p[j]] += delta, v[j] -= delta;
             else dist[j] -= delta;
         }
         j0 = j1;
     }while(p[j0]);
     while(j0){ // update alternating path
         int j1 = pre[j0];
         p[j0] = p[j1], j0 = j1;
     }
    }
    for(int j = 1; j < m; ++ j) if(p[j]) res[p[j] - 1] = j - 1;
    return {-v[0], res};
} // O(V^2 E)