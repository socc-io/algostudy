//
//  floydWarshall.h
//  DailyCodingTeamNote
//
//  Created by MaybeS on 10/3/15.
//  Copyright (c) 2015 Maybe. All rights reserved.
//
#pragma once
#include <vector>

using namespace std;

template<typename type>
void floydWarshall(vector< vector<type> >& map)
{
	for(int k = 0; k< map.size(); k++)
		for(int i = 0; i < map.size(); i++)
			for(int j = 0; j< map.size(); j++)
				if(map[i][j] > map[i][k] + map[k][j])
					map[i][j] = map[i][k] + map[k][j];
}
