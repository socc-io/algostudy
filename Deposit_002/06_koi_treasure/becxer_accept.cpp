
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <set>
#include <algorithm>
#include <cstdlib>    // for atoi
#include <sstream>    // for stringstream
#include <cmath>    // for sqrt
#include <cstring>    // for memset
using namespace std;

#define INF 2139999999

char map2[100][100];
int cap[100][100];
int row,col;
int dx[4] = {1,0,-1,0};
int dy[4] = {0,1,0,-1};

class Point{
public:
	int x,y;
	Point(int _x,int _y):x(_x),y(_y){}
};

Point* queue1[5000];
int head = 0;
int top = 0;
void push(Point* p) { queue1[top++] = p; }
Point* front() { return queue1[head++]; }
void init() { head = 0 ; top = 0;}
bool empty() { return head == top ;}
bool isValid(int new_r, int new_c) {
	return ( new_r < 0  || new_r >= row  || new_c < 0
		|| new_c >= col || cap[new_r][new_c] == -1)? false: true;
}

int max_path =0;

void cpMap2Cap(){
	for(int  i = 0  ; i < row ; i++) {
		for( int j = 0 ; j < col ; j++) {
			if(map2[i][j] == 'L') cap[i][j] = 0;
			if(map2[i][j] == 'W') cap[i][j] = -1;
		}
	}
}

int main(void) {
	cin >> row >> col;
	for(int i = 0 ; i < row ; i++) {
		cin >> map2[i];
	}

	for(int i= 0 ; i < row ; i++){
		for(int j = 0 ; j < col ; j++){
			int sx = i; int sy = j;
			if(map2[sx][sy] =='L'){
				cpMap2Cap();
				init();
				push(new Point(sx, sy));
				while(true){
					if(empty()) break;
					Point* now = front();
					max_path = (cap[now->x][now->y] > max_path)?
					 cap[now->x][now->y] : max_path;
					for(int p = 0; p < 4 ; p++){
						int new_x = now->x + dx[p];
						int new_y = now->y + dy[p];
						if(isValid(new_x,new_y)){
							if(cap[new_x][new_y] == 0 || cap[new_x][new_y] > cap[now->x][now->y]+1){
								cap[new_x][new_y] = cap[now->x][now->y] + 1;
								push(new Point(new_x,new_y));
							}
						}
					}
				}
			}
		}
	}
	cout << max_path << endl;
  return 0;
}
