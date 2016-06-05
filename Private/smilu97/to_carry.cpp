#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>

using namespace std;

#define MATH_PI 3.1415f

class Vertex
{
public :
	int next;
	int prev;
	bool connected;
	float x;
	float y;
	float angle;
	float distance;
	Vertex()
	{
		next = -1;
		prev = -1;
		connected = false;
		x = -1;
		y = -1;
		angle = -1;
		distance = -1;
	}
	bool operator>(Vertex tmp){
		if(this->angle > tmp.angle){
			return true;
		}
		return false;
	}
	bool operator<(Vertex tmp){
		if(this->angle < tmp.angle){
			return true;
		}
		return false;
	}
	void SetDistance(int _x, int _y)
	{
		float deltax = x - _x;
		float deltay = y - _y;
		distance = deltax*deltax + deltay*deltay;
	}
}

int center_x, center_y;
int vertex_num;
vector<Vertex> vertices;

bool CheckAndUpdate(int index)
{
	float mid_len = vertices[index].distance;
	float b_len = vertices[vertices[index].prev].distnace;
	float a_len = vertices[vertices[index].next].distance;
	float mid_len2 = mid_len*mid_len;
	float a_len2 = a_len*a_len;
	float b_len2 = b_len*b_len;
	float bd_len2 = mid_len2 + b_len2 - 2*mid_len*b_len*cos(vertices[index].angle-vertices[vertices[index].prev].angle);
	float ad_len2 = mid_len2 + a_len2 - 2*mid_len*a_len*cos(vertices[vertices[index].next].angle - vertices[index].angle);
	float a_angle = acos((ad_len2 + mid_len2 - a_len2) / (2*sqrt(ad_len2)*mid_len));
	float b_angle = acos((bd_len2 + mid_len2 - b_len2) / (2*sqrt(bd_len2)*mid_len));
	float angle_sum = a_angle + b_angle;
	if(angle_sum > MATH_PI){
		vertices[vertices[index].prev].next = vertices[index].next;
		vertices[vertices[index].next].prev = vertices[index].prev;
		vertices[index].connected = false;
		return true;
	}
	return false;

void GetLength(int from, int to)
{
	int deltax = vertices[from].x - vertices[to].x;
	int deltay = vertices[from].y - vertices[to].y;
	return sqrt(deltax*deltax + deltay*deltay);
}

int main(void)
{
	cin >> vertex_num;
	vertices.resize(vertex_num);
	for(int i=0;i<vertex_num;++i){
		cin >> vertices[i].x >> vertices[i].y;
	}
	int sum_x, sum_y;
	for(int i=0;i<vertex_num;++i){
		sum_x += vertices[i].x;
		sum_y += vertices[i].y;
	}
	center_x = sum_x / vertex_num;
	center_y = sum_y / vertex_num;
	for(int i=0;i<vertex_num;++i){
		int gradient = (vertices[i].second - center_y) /
		 	(vertices[i].first - center_x);
		vertices[i].angle = atan(gradient);
	}
	sort(vertices);
	vertices[0].next = 1;
	vertices[0].prev = vertex_num-1;
	vertices[vertex_num-1].next = 0;
	vertices[vertex_num-1].prev = vertex_num-2;
	for(int i=1;i<vertex_num-1;++i){
		vertices[i].next = i+1;
		vertices[i].prev = i-1;
		vertices[i].connected = true;
	}
	for(int i=0;i<vertex_num;++i){
		vertices[i].SetDistance(center_x. center_y);
	}
	bool updated = true;
	while(updated)
	{
		updated = false;
		for(int i=0;i<vertex_num;++i){
			if(vertices[i].connected == true)
			{
				if(CheckAndUpdate(i)){
					updated = true;
				}
			}
		}
	}
	int sum_length = 0;
	for(int i=0;i<vertex_num;++i)
	{
		if(vertices[i].connected)
		{
			sum_length += GetLength(i, vertices[i].to);
		}
	}
	cout << "Sum of connected edges : " << sum_length << endl;
}