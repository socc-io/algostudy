//
//  convex_hull.h
//  DailyCodingTeamNote
//
//  Created by MaybeS on 10/3/15.
//  Copyright (c) 2015 Maybe. All rights reserved.
//
#pragma warning (disable :4996)
#pragma once
#include <utility>
#include <vector>
#include <algorithm>
using namespace std;
//ConvexHull
template<typename type>
type cross(const pair<type, type> &O, const pair<type, type> &A, const pair<type, type> &B)
{
    return (type)(A.first - O.first) * (B.second - O.second) - (type)(A.second - O.second) * (B.first - O.first);
}

// param:: vector of Point with x,y coordinates in long long int, P.size >= 3
// return:: convex_hull with x, y coordinates in long long int
// the first and the last element is SAME
template<typename type>
vector<pair<type, type> > convex_hull(vector<pair<type, type> > map)
{
    int k = 0;
    vector<pair<type, type> > result(2 * map.size());
    sort(map.begin(), map.end(), [](pair<type, type> p, pair<type, type> q) { return p.second > q.second || ((!(p.second < q.second) && p.first < q.first)); });
    for (int i = 0; i < map.size(); ++i)
    {
        while (k >= 2 && cross<type>(result[k - 2], result[k - 1], map[i]) <= 0)
            k--;
        result[k++] = map[i];
    }
    for (int i = map.size() - 2, t = k + 1; i >= 0; i--)
    {
        while (k >= t && cross<type>(result[k - 2], result[k - 1], map[i]) <= 0)
            k--;
        result[k++] = map[i];
    }
    result.resize(k);
    return result;
}