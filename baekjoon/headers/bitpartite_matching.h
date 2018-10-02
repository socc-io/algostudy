//
//  bitpartite_matching.h
//
//  Updated by Prev on 16.6.2
//

#include <stdio.h>
#include <string.h>
#include <vector>

#pragma once

#ifndef _bitpartite_matching_h
#define _bitpartite_matching_h
#endif

using namespace std;

vector<vector<int> > adj;
vector<int> a_match, b_match;
vector<bool> visited;

bool dfs(int a){
	if (visited[a]) return false;
	visited[a] = true;
	
	for (auto b: adj[a]) {
		if (b_match[b] == -1 || dfs(b_match[b])) {
			a_match[a] = b;
			b_match[b] = a;
			return true;
		}
	}
	
	return false;
}

int bipartiteMatch(int n, int m){
	a_match.assign(n, -1);
	b_match.assign(m, -1);
	
	int ret = 0;
	
	for (int s = 0; s < n; ++s){
		visited.assign(n, false);
		if (dfs(s)) ++ret;
	}
	
	return ret;
}

/*
boj 11375

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	
	adj.resize(n);
	
	for (int i=0; i<n; i++) {
		int k;
		scanf("%d", &k);
		
		for (int j=0; j<k; j++) {
			int x;
			scanf("%d", &x);
			
			adj[i].push_back( x-1 );
		}
	}
	
	printf("%d", bipartiteMatch(n, m));
	
	return 0;
}
*/





