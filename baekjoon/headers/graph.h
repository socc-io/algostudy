#pragma once

#include <vector>
#include <queue>
#include <list>
#include <map>
#include <unordered_map>

#include <iostream>
#include <functional>
#include <algorithm>

#define MAX_VERTEX	SIZE_MAX
#define MAX_COUNT	SIZE_MAX

#define _GRAPH_DIRECTION		0
#define _GRAPH_UNDIRECTION		1

#define _GRAPH_NOVALUE			0
#define _GRAPH_VALUE			2
/* GRAPH_TYPE DEFINITION _ x, y, ab bits
{x|DIRECTION, y|DATATYPE, ab|TYPE} */


template < typename _count_type, typename _value_type >
class GRAPH_RAW_DATA
{
private:
	std::vector < std::vector < _value_type > > graph;
public:
	GRAPH_RAW_DATA() {}
	~GRAPH_RAW_DATA() {}
	void initialize(_count_type count)
	{
		std::vector < _value_type > temp(count + 1);
		graph.assign(count + 1, temp);
	}
	void insert(_count_type start, _count_type dest, _value_type value)
	{
		graph[start][dest] += value;
	}
	void insert(_count_type start, _count_type dest)
	{
		graph[start][dest] = 1;
	}
	std::vector < _value_type > find(_count_type start)
	{
		return graph[start];
	}
	_value_type find(_count_type start, _count_type dest)
	{
		return graph[start][dest];
	}
};

template < typename _count_type, typename _value_type >
class GRAPH_RAW
{
private:
	unsigned int type;
	GRAPH_RAW_DATA < _count_type, _value_type > graph;
public:
	_count_type vertex_count;
	GRAPH_RAW(unsigned int type)
	{
		this->type = type;
	}
	~GRAPH_RAW()
	{}
	void initialize(_count_type vertex_count, _value_type line_count)
	{
		this->vertex_count = vertex_count;
		graph.initialize(vertex_count);
		for (int count = 0; count < line_count; count++)
		{
			int t_start, t_dest, t_value = 1;
			std::cin >> t_start >> t_dest;
			if (type >> 1)
			{
				std::cin >> t_value;
				insert(t_start, t_dest, t_value);
			}
			else
				insert(t_start, t_dest);
		}
	}
	void insert(_count_type start, _count_type dest, _value_type value)
	{
		if (type % 2)
		{
			graph.insert(start, dest, value);
			graph.insert(dest, start, value);
		}
		else
			graph.insert(start, dest, value);
	}
	void insert(_count_type start, _count_type dest)
	{
		if (type % 2)
		{
			graph.insert(start, dest);
			graph.insert(dest, start);
		}
		else
			graph.insert(start, dest);
	}
	std::vector<_value_type> connection(_count_type start)
	{
		return graph.find(start);
	}
	_value_type connection(_count_type start, _count_type dest)
	{
		return graph.find(start, dest);
	}
	_value_type find_short_of(_count_type start, _count_type dest)
	{
		std::vector < _value_type > list(this->vertex_count + 1, MAX_COUNT);
		std::vector < bool > chk(this->vertex_count + 1, false);

		list.at(start) = 0;

		while (!chk.at(dest))
		{
			std::priority_queue < std::pair <_count_type, _value_type>, std::vector < std::pair <_value_type, _count_type> >, std::greater < std::pair < _value_type, _count_type > > > pq;

			for (_count_type count = 0; count < this->vertex_count + 1; count++)
				pq.push({ list.at(count), count });

			while (chk.at(pq.top().second)) pq.pop();

			chk.at(pq.top().second) = true;
			std::vector < _value_type > connect = this->connection(pq.top().second);

			for (_count_type count = 1; count < this->vertex_count + 1; count++)
				if (connect.at(count) && list.at(count) > list.at(pq.top().second) + connect.at(count))
				{
					list.at(count) = list.at(pq.top().second) + connect.at(count);
					chk.at(count) = false;
				}
		}

		if (list.at(dest) == MAX_COUNT)
			return -1;
		else
			return list.at(dest);
	}
	_value_type find_long_of(_count_type start, _count_type dest)
	{

	}
};
template < typename _count_type, typename _value_type >
class GRAPH_ADJACENCY : public GRAPH_RAW < _count_type, _value_type >
{
private:

public:
	GRAPH_ADJACENCY(unsigned int type) : GRAPH_RAW(type)
	{}
	~GRAPH_ADJACENCY()
	{}
};