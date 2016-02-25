#include <iostream>
#include <vector>
#include <stack>
using namespace std;

#define MAX 99999999
int N; // 정점
int start;
int M; // 간선

int minDistance(int dist[], bool sptSet[])
{
	int min = MAX, min_index;

	for (int v = 1; v <= N; v++)
	{
		if (sptSet[v] == false && dist[v] <= min)
		{
			min = dist[v]; // 최소거리
			min_index = v; // 
		}

	}
	return min_index;
}

class Graph // 큐
{
	int v;
	vector< vector<int> > adj;
public:
	Graph(int V);
	void addEdge(int v, int w, int distanse);
	void dijkstra(int src);
};

Graph::Graph(int V)
{
	this->v = V;

	for (int i = 0; i < v + 1; ++i)
	{
		vector<int> element;
		element.resize(v + 1);
		adj.push_back(element);
	}

}

void Graph::addEdge(int v, int w, int distanse)
{
	adj[v][w] = distanse;
	//adj[w][v] = distanse;
}

void Graph::dijkstra(int src)
{
	int dist[1001];
	bool sptSet[1001];
	int path[1001];
	bool check = false;


	for (int i = 0; i < 1001; i++)
		dist[i] = MAX, sptSet[i] = false;

	int k = -1;
	dist[src] = 0;
	

	for (int count = 1; count <= N; count++)
	{
		path[0] = src;
		k = minDistance(dist, sptSet);
		sptSet[k] = true;

		for (int j = 1; j <= N; j++)
		{			
			if (!sptSet[j] && adj[k][j] && dist[k] != MAX && dist[k] + adj[k][j] < dist[j])
			{
				dist[j] = dist[k] + adj[k][j];
				path[j] = k;
			}
		}
	}

	for (int i = 1; i <= N; i++)
	{
		stack<int> s;
		s.push(MAX);

		for (int j = i; j != src; j = path[j])
			s.push(j);

		cout << src << " ";

		for (int j; (j = s.top()) != MAX; s.pop())
			cout << j << " ";

		cout << endl;
	}

}


int main()
{
	cin >> N >> M >> start;
	Graph g(N);

	int num1, num2, num3;
	for (int i = 0; i < M; i++)
	{
		cin >> num1 >> num2 >> num3;
		g.addEdge(num1, num2, num3);
	}

	g.dijkstra(start);

}