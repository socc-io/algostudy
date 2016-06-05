
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
#define OUT 0
#define IN 1
#define CHEESE 2
#define DELETE 3

int row,col,temp;
int cmap[1000][1000];
int visit[1000][1000];
int tcount = 0;

int dx[4] = {1,-1,0,0};
int dy[4] = {0,0,1,-1};

bool is_valid(int new_x, int new_y){
	return !(new_x < 0 || new_y < 0 || new_x >= row || new_y >= col);
}

void find_outter(int x, int y){
	cmap[x][y] = OUT;
	visit[x][y] = 1;
	for(int i = 0 ; i < 4 ;i++){
		int nx = x + dx[i];
		int ny = y + dy[i];
		if(is_valid(nx,ny)){
			if(cmap[nx][ny] != CHEESE && visit[nx][ny] != 1){
				find_outter(nx,ny);
			}
		}
	}
}

void kill_cheese(){
	for(int i = 0; i < row ; i++){
		for(int j = 0 ; j < col ; j++){
			int count = 0;
			for(int p = 0 ; p < 4 ; p ++){
				int nx = i + dx[p];
				int ny = j + dy[p];
				if(is_valid(nx,ny) && cmap[nx][ny] == OUT){
					count += 1;
				}
			}
			if( count >= 2 ) visit[i][j] = DELETE;
		}
	}
}

bool check_end(){
	bool isCheeseExist = false;
	for(int i = 0; i < row ; i++){
		for(int j = 0 ; j < col ; j++){
			if(visit[i][j] == DELETE) cmap[i][j] = OUT;
			visit[i][j] = 0;
			if(cmap[i][j] == CHEESE) isCheeseExist = true;
		}
	}
	return isCheeseExist;
}


void print_map(){
	cout << "==========="<< endl;
	for(int i = 0; i < row ; i++){
		for(int j = 0 ; j < col ; j++){
			cout << cmap[i][j] << " ";
		}
		cout << endl;
	}
}


int main(void) {
	cin >> row >> col;
	for(int i = 0 ; i < row ; i++){
		for(int j = 0 ; j < col ; j++){
			cin >> temp;
			cmap[i][j] = (temp == 1)? CHEESE : IN;
		}
	}
	while(check_end()){
		//print_map();
		find_outter(0,0);
		//print_map();
		kill_cheese();
		//print_map();
		tcount += 1;
	}
	cout << tcount << endl;
    return 0;
}
