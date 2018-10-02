//
//  hamiltonCycle.h
//  DailyCodingTeamNote
//
//  Created by MaybeS on 10/3/15.
//  Copyright (c) 2015 Maybe. All rights reserved.
//

#pragma once
#include <vector>

using namespace std;
//HamiltonCircuit
//input vector<vector<boo>> map;
bool hamiltonCycle_sub(vector<vector<bool> > map, vector<int> path, int pos)
{
	if(pos == map.size())
		if(map[path[pos-1]][path[0]]==1)
			return true;
		else
			return false;

	for(int i = 1; i < map.size(); i++)
	{
		if(map[path[pos-1]][i])
		{
			bool chk = true;
			for(int j = 0; j < pos; j++)
				if(path[j]==i)
				{
					chk = false;
					break;
				}
			if(chk)
			{
				path[pos] = i;
				if(hamiltonCycle_sub(map,path,pos+1))
					return true;
				path[pos] = -1;
			}
		}
	}
	return false;
}
bool hamiltonCycle(vector<vector<bool> > map)
{
	vector<int> path(map.size(),-1);
	path[0] = 0;
	if(!hamiltonCycle_sub(map,path,1))
	{
		//No solution
		return false;
	}
	//path == solution
	return true;
}