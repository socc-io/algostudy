#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

int vertex_num;
int edge_num;
int *network;
int *virused;
int virused_num = 0;

void explore(int position)
{
	for(int i=0;i<vertex_num;++i) {
		if(network[position*vertex_num+i] != 1) continue;
		if(i == position) continue;
		if(virused[i] == true) continue;
		virused_num++;
		virused[i] = true;
		explore(i);
	}
}

int main(int argc, char** argv)
{
	cin >> vertex_num >> edge_num;
	network = (int*)malloc(sizeof(int)*vertex_num*vertex_num);
	virused = (int*)malloc(sizeof(int)*vertex_num);
	int ver2 = vertex_num * vertex_num;
	for(int i=0;i<ver2;++i) network[i] = -1; 
	for(int i=0;i<vertex_num;++i) virused[i] = false;
	for(int i=0;i<edge_num;++i) {
		int a, b;
		cin >> a >> b;
		--a;
		--b;
		network[a*vertex_num+b] = 1;
		network[b*vertex_num+a] = 1;
	}
	virused[0] = true;
	explore(0);
	printf("%d", virused_num);
	free(network);
	free(virused);
	return 0;
}