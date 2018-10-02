//
//  dijkstra.h
//  DailyCodingTeamNote
//
//  Created by MaybeS on 10/3/15.
//  Copyright (c) 2015 Maybe. All rights reserved.
//
#pragma once
#include <queue>
#include <vector>
#include <utility>

using namespace std;
//Dijkstra.h 18/34
//map[i][j]={x,y}--i:index,j:start,x:end,y:cost
//dist[i]=j--i:end,j:cost
//start
template<typename t_index, typename t_cost>
void dijkstra(const vector<vector<pair<t_index, t_cost>>>& map, vector<t_cost>& dist, const size_t& start)
{
	priority_queue<pair<t_index, t_cost>> pq;
	pq.push({ start, 0 });
	while (pq.size())
	{
		pair<t_index, t_cost> now = pq.top();
		pq.pop();
		for (int i = 0; i < map[now.first].size(); i++)
		{
			t_index next_index = map[now.first][i].first;
			if (dist[next_index] > -now.second + map[now.first][i].second)
			{
				dist[next_index] = -now.second + map[now.first][i].second;
				pq.push({ next_index, -dist[next_index] });
			}
		}
	}
}