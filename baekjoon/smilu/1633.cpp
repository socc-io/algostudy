#include <iostream>
#include <cstdlib>

#include <vector>
#include <set>
#include <deque> 
#include <algorithm>

using namespace std;

typedef pair<int, int> pii;

#define INF 0x3FFFFFFF

struct edge
{
	int from;
	int to;
	int capa;
	int cost;
};

bool SPFA(vector< vector<edge*> > &edges_of, vector<edge*> &prev) // Shortest Path Faster Algorithm
{
	int n = edges_of.size();
	for(auto it = prev.begin(); it != prev.end(); ++it) (*it) = 0;
	vector<int> d(n, INF);
	deque<int> Q;
	Q.push_back(0);
	d[0] = 0;
	while(!(Q.empty()))
	{
		int u = Q.front(); Q.pop_front();
		for(auto it = edges_of[u].begin(); it != edges_of[u].end(); ++it)
		{
			if((*it)->capa <= 0) continue;
			int v = (*it)->to;
			int new_d = d[u] + (*it)->cost;
			if(new_d < d[v]) {
				d[v] = new_d;
				prev[v] = (*it);
				bool already = false;
				for(auto it2 = Q.begin(); it2 != Q.end(); ++it2) {
					if((*it2) == v) { already=true; break; }
				}
				if(!already) Q.push_back(v);
			}
		}
	}
	return d[n-1] != INF;
}

int RebuildGraph(vector< vector<edge*> > &edges_of, vector<edge*> &prev)
{
	int n = edges_of.size();
	int cur = n-1;
	int min_cap = INF;
	while(prev[cur] != NULL)
	{
		if(prev[cur]->capa < min_cap) {
			min_cap = prev[cur]->capa;
		}
		cur = prev[cur]->from;
	}
	cur = n-1;
	int cost_sum = 0;
	while(prev[cur] != NULL)
	{
		edge* pe = prev[cur];
		cost_sum += pe->cost;
		pe->capa -= min_cap;
		bool already = false;
		for(auto it = edges_of[pe->to].begin(); it != edges_of[pe->to].end(); ++it) {
			if((*it)->to == pe->from) { 
				already = true;
				(*it)->capa -= min_cap;
				break; 
			}
		}
		if(!already) {
			edge* tmp_edge = new edge{pe->to, pe->from, min_cap, pe->cost * (-1)};
			edges_of[pe->to].push_back(tmp_edge);
		}
		cur = prev[cur]->from;
	}
	return min_cap * cost_sum;
}

int main(int argc, char** argv)
{
	int tmp_w, tmp_b, i;
	vector<pii> people;
	while(cin >> tmp_w >> tmp_b)
	{
		people.push_back({tmp_w, tmp_b});
	}
	// Sort with white skill and black skill
	vector<int> ow_people(people.size()), ob_people(people.size());
	for(int i=0;i<people.size();++i) {
		ow_people[i] = i;
		ob_people[i] = i;
	}
	sort(ow_people.begin(), ow_people.end(), [&](int a, int b) {
		return people[a].first > people[b].first;
	});
	sort(ob_people.begin(), ob_people.end(), [&](int a, int b) {
		return people[a].second > people[b].second;
	});
	// check duplication
	set<int> sw, sb, sc;
	for(int i=0;i<30;++i) {
		sw.insert(ow_people[i]);
		sb.insert(ob_people[i]);
	}
	for(auto it = sw.begin(); it != sw.end(); ++it) {
		if(sb.find((*it)) != sb.end()) {
			sc.insert((*it));
		}
	}
	for(auto it = sc.begin(); it != sc.end(); ++it) {
		sw.erase((*it));
		sb.erase((*it));
	}
	int sw_size = sw.size();
	int sb_size = sb.size();
	int sc_size = sc.size();
	int ss_size = sw_size + sb_size + sc_size;
	// Building graph
	int graph_size = 4 + ss_size;
	vector< vector<edge*> > edges_of(graph_size);
	edge* tmp_pe;
	//// first layer
	tmp_pe = new edge{0, 1, 15, 0};
	edges_of[0].push_back(tmp_pe);
	tmp_pe = new edge{0, 2, 15, 0};
	edges_of[0].push_back(tmp_pe);
	//// second layer
	i=3;
	for(auto it = sw.begin(); it != sw.end(); ++it, ++i) {
		tmp_pe = new edge{1, i, 1, people[(*it)].first * (-1)};
		edges_of[1].push_back(tmp_pe);
	}
	i=3+sw_size;
	for(auto it = sb.begin(); it != sb.end(); ++it, ++i) {
		tmp_pe = new edge{2, i, 1, people[(*it)].second * (-1)};
		edges_of[2].push_back(tmp_pe);
	}
	i=3+sw_size+sb_size;
	for(auto it = sc.begin(); it != sc.end(); ++it, ++i) {
		tmp_pe = new edge{1, i, 1, people[(*it)].first * (-1)};
		edges_of[1].push_back(tmp_pe);
		tmp_pe = new edge{2, i, 1, people[(*it)].second * (-1)};
		edges_of[2].push_back(tmp_pe);
	}
	//// Third layer
	for(int i=0;i<ss_size;++i) {
		tmp_pe = new edge{3+i, graph_size-1, 1, 0};
		edges_of[3+i].push_back(tmp_pe);
	}
	// MCMF
	vector<edge*> prev(graph_size);
	int cost_sum = 0;
	while(SPFA(edges_of, prev)) {
		int cost = RebuildGraph(edges_of, prev);
		cost_sum -= cost;
	}
	// print result
	cout << cost_sum;
	// delete
	for(auto it1 = edges_of.begin(); it1 != edges_of.end(); ++it1) {
		for(auto it2 = it1->begin(); it2 != it1->end(); ++it2) {
			delete (*it2);
		}
	}
	return 0;
}