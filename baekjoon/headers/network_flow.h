//
//  network_flow.h
//  TEJAVA TeamNote
//
//  Created by Prev on 3/28/16.
//  Copyright (c) 2016 Prev. All rights reserved.
//


#include <math.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <unordered_map>

#define INF 1987654321

using namespace std;


typedef int node_value;

struct Node;
struct Edge;

struct Edge {
	Node* target;
	Edge* reverse;
	int capacity, flow;
	
	Edge() {
		this->flow = 0;
	}
	
	Edge(Node* target, int capacity) {
		this->target = target;
		this->capacity = capacity;
		this->flow = 0;
	}
	
	int getRestCapacity() {
		return capacity - flow;
	}
	void push(int amt){
		flow += amt;
		this->reverse->flow -= amt;
	}
};

struct Node {
	vector<Edge*> edges;
	node_value value;
	
	Node() {}
	Node(node_value val) { this->value = val; }
	
	void connectTo(Node* target, int capacity) {
		Edge *e = new Edge(target, capacity);
		Edge *e_rev = new Edge(this, 0);
		
		e->reverse = e_rev;
		e_rev->reverse = e;
		
		this->edges.push_back( e );
		target->edges.push_back( e_rev );
	}
};

int networkFlow(Node* source, Node* sink) {
	int totalAmount = 0;
	
	while (true) {
		queue< Node* > que;
		unordered_map<Node*, Edge*> track;
		
		que.push( source );
		
		// 경로 탐색
		while (!que.empty() && track[sink] == nullptr) {
			Node* here = que.front();
			que.pop();
			
			for (int k=0; k<here->edges.size(); k++) {
				Edge* e = here->edges[k];
				
				if (e->getRestCapacity() > 0 && track[e->target] == nullptr) {
					que.push( e->target );
					track[ e->target ] = e->reverse;
				}
			}
		}
		
		if (track[sink] == nullptr) break;
		
		// 최소 유량 얻음
		int amount = INF;
		for (Node* n = sink; n != source; n = track[n]->target)
			amount = min(amount, track[n]->reverse->getRestCapacity());
		
		// 유량 갱신
		for (Node* n = sink; n != source; n = track[n]->target)
			track[n]->push( -amount );
		
		totalAmount += amount;
	}
	
	return totalAmount;
}


/*
int main() {
	// https://www.acmicpc.net/problem/2188
	
	int N, M;
	scanf("%d %d", &N, &M);
	
	Node* source = new Node;
	Node* sink = new Node;
	
	vector<Node*> cows(N);
	vector<Node*> sheds(M);
	
	for (int i=0; i<N; i++) {
		cows[i] = new Node(i+1);
		source->connectTo(cows[i], 1);
	}
	
	for (int i=0; i<M; i++) {
		sheds[i] = new Node(i+1);
		sheds[i]->connectTo(sink, 1);
	}
	
	for (int i=0; i<N; i++) {
		int si;
		scanf("%d", &si);
		
		for (int j=0; j<si; j++) {
			int x;
			scanf("%d", &x);
			
			cows[i]->connectTo(sheds[x-1], 1);
		}
	}
	
	
	int ret = networkFlow(source, sink);
	printf("%d", ret);
	
	return 0;
}
*/

