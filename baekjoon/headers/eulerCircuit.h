//
//  eulerCircuit.h
//  DailyCodingTeamNote
//
//  Created by MaybeS on 10/3/15.
//  Copyright (c) 2015 Maybe. All rights reserved.
//
#pragma once
#include <queue>
#include <vector>
#include <utility>
#include <list>

using namespace std;

class euler {
	int V;    			// No. of vertices
    list<int> *adj;    	// A dynamic array of adjacency lists
public:
    euler(vector<int> map)
    {
    	this->V = map.size();
    	for(int i = 0 ; i < map.size(); i++)
    		this->addEdge(i,map.at(i));
    }
    euler(int V)   {this->V = V; adj = new list<int>[V]; }
    ~euler() { delete [] adj; } 
    void addEdge(int v, int w);
    int isEulerian();
    bool isConnected();
    void DFSUtil(int v, bool visited[]);
};
void euler::addEdge(int v, int w)
{
    adj[v].push_back(w);
    adj[w].push_back(v);  // Note: the graph is undirected
}
void euler::DFSUtil(int v, bool visited[])
{
    visited[v] = true;
    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if (!visited[*i])
            DFSUtil(*i, visited);
}
 
bool euler::isConnected()
{
    bool visited[V];
    int i;
    for (i = 0; i < V; i++)
        visited[i] = false;
    for (i = 0; i < V; i++)
        if (adj[i].size() != 0)
            break;
    if (i == V)
        return true;
    DFSUtil(i, visited);
    for (i = 0; i < V; i++)
       if (visited[i] == false && adj[i].size() > 0)
            return false;
 
    return true;
}
int euler::isEulerian()
{
    // Check if all non-zero degree vertices are connected
    if (isConnected() == false)
        return 0;
    // Count vertices with odd degree
    int odd = 0;
    for (int i = 0; i < V; i++)
        if (adj[i].size() & 1)
            odd++;
    // If count is more than 2, then graph is not Eulerian
    if (odd > 2)
        return 0;
    // If odd count is 2, then semi-eulerian.
    // If odd count is 0, then eulerian
    // Note that odd count can never be 1 for undirected graph
    return (odd)? 1 : 2;
}