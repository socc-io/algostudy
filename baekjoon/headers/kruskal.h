//
// kruskal.h
//
// kruskal algorithm by greedy
//
// INPUT: vector (directed, weighted graph)
//
// OUTPUT: minimum spanning tree
//
// Time: 	O(ElogV)
//			E: vertices, V: edges
//


#include <algorithm>
#include <vector>
#include <utility>

#define P(T) std::pair<T, T>
#define PP(T, Tt) std::pair<P(T), Tt>
#define VP(T) std::vector<P(T)>
#define VPP(T, Tt) std::vector<PP(T, Tt)>

using  namespace std;
template<typename T>
T kruskal_find(VP(T)& subsets, T i)
{
	if (subsets[i].first - i)
		subsets[i].first = kruskal_find(subsets, subsets[i].first);
	return subsets[i].first;
}
template<typename T>
void kruskal_union(VP(T)& subsets, T x, T y)
{
	T xroot = kruskal_find<T>(subsets, x);
	T yroot = kruskal_find<T>(subsets, y);

	if (subsets[xroot].second < subsets[yroot].second)
		subsets[xroot].first = yroot;
	else if (subsets[xroot].second > subsets[yroot].second)
		subsets[yroot].first = xroot;
	else
	{
		subsets[yroot].first = xroot;
		subsets[xroot].second++;
	}
}
/*input vector<{{start,end},value}>*/
template<typename Te, typename Tv>
VPP(Te, Tv) kruskal(VPP(Te, Tv)& graph, const Te& V)
{
	sort(graph.begin(), graph.end(), [](PP(Te, Tv) p, PP(Te, Tv) q) { return p.second < q.second; });
	Te idx = 0;
	VPP(Te, Tv) result;
	VP(Te) subsets(V);

	for (Te v = 0; v < V; v++)
		subsets[v] = { v, 0 };

	while (result.size() < V - 1)
	{
		PP(Te, Tv) next = graph[idx++];
		Te x = kruskal_find<Te>(subsets, next.first.first);
		Te y = kruskal_find<Te>(subsets, next.first.second);

		if (x - y)
		{
			result.push_back(next);
			kruskal_union<Te>(subsets, x, y);
		}
	}
	return result;
}