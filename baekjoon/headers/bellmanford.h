//
// bellmanford.h
//
// path find, bellmanford
//
// INPUT: graph
//
// OUTPUT: pair<path dist(s to t), vector<path>>
//
// Time: O(NlogN)
//	
#include <vector>
#include <algorithm>

#define INF 123456789
using namespace std;
template<typename T>
pair<int, vector<size_t>> bellmanford(vector<vector<pair<int,int>>> g, int s, int t)
{
	vector<int> dist(g.V, INF);
	vector<int> parent(g.V, -1);
	dist[s] = 0;
	for (int i = 0; i < g.size(); i++)
		for (int j = 0; j < g[i].size(); j++)
			if (dist[g[i][j].first] > dist[i] + g[i][j].second)
			{
				dist[g[i][j].first] = dist[i] + g[i][j].second;
				prent[i] = g[i][j].first;
			}

	vector<size_t> result;
	for (int i = t; t != -1; t = parent[t])
		result.push_back(t);
	vector<size_t> rresult(result.rbegin(), result.rend());
	return {dist[t], rresult}
}