//
//  scv_backtracking.cpp
//  algostudy_C++
//
//  Created by BaekSeoHyeon on 2015. 2. 8..
//  Copyright (c) 2015년 BaekSeoHyeon. All rights reserved.

#include <iostream>

using namespace std;

int map[100][100] = {{0,},};
int size = 0;

int dx[2] = {0,1};
int dy[2] = {1,0};

bool isvalid(int x, int y){
    return (x < 0 || y <0 || x >= size || y>= size)? false : true;
}


class Path{
public:
    int mineral;
    int x;
    int y;
    
    bool isGoal(){
        return (x == size-1 && y == size-1)? true : false;
    };
    
    Path(int x, int y, int mineral){
        this->x = x;
        this->y = y;
        this->mineral = mineral;
    }
    
    Path* createNextPath(int type){
        Path* nextPath = NULL;
        if(isvalid(this->x+dx[type],this->y+dy[type])){
            nextPath = new Path(this->x+dx[type],this->y+dy[type],0);
            nextPath->mineral = this->mineral + map[nextPath->x][nextPath->y];
        }
        return nextPath;
    };
};

//-----------------------stack-----------------------

Path* stack[1000000];
int top = 0;

void push(Path* p){
    stack[top++] = p;
}

Path* pop(){
    return stack[--top];
}

bool isEmpty(){
    return (top == 0)? true:false;
}

//--------------------------------------------------

int solve_with_backtrack(){
    int max_mineral = 0;
    Path* first = new Path(0,0,map[0][0]);
    push(first);
    while(true){
        if(isEmpty()){
            break;
        }
        Path* now = pop();
        cout << "visit : " << now->x << "," << now->y << endl;
        max_mineral = (now->isGoal() && now->mineral > max_mineral)? now->mineral : max_mineral;
        for(int candy = 0 ; candy < 2 ; candy++){
            Path* candidate = now->createNextPath(candy);
            if(candidate != NULL){
                push(candidate);
            }
        }
        delete(now);
    }
    
    return max_mineral;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    cin >> size;
    
    for(int i= 0 ; i < size ; i++){
        for(int j = 0; j < size ; j++){
            cin >> map[i][j];
        }
    }
    cout << solve_with_backtrack() << endl;
    return 0;
}
