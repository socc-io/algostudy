//
//  main.cpp
//  algostudy_C++
//
//  Created by BaekSeoHyeon on 2015. 2. 8..
//  Copyright (c) 2015년 BaekSeoHyeon. All rights reserved.
//

#include <iostream>
using namespace std;

int map[100][100] = {{0,},};
int scv_max[100][100] = {{0,},};
int size = 0;

int dx[2] = {0,1};
int dy[2] = {1,0};

bool isvalid(int x, int y){
    if(x < 0 || y <0 || x >= size || y>= size)
        return false;
    else
        return true;
}

int solve_with_dp(){
    for(int i = 0 ; i < size ; i++){
        for(int j = 0 ; j < size ;j++){
            for(int  p= 0 ; p < 2 ; p++){
                int x = i+ dx[p];
                int y = j+ dy[p];
                if( isvalid(x,y) && scv_max[x][y] <= scv_max[i][j] + map[x][y] ){
                    scv_max[x][y] = scv_max[i][j] + map[x][y];
                }
            }
        }
    }
    return scv_max[size-1][size-1];
}

int main(int argc, const char * argv[]) {
    // insert code here...
    cin >> size;
    
    for(int i= 0 ; i < size ; i++){
        for(int j = 0; j < size ; j++){
            cin >> map[i][j];
        }
    }
    scv_max[0][0] = map[0][0];
    cout << solve_with_dp() << endl;
    return 0;
}
