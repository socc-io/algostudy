#include <vector>

using namespace std;

const int MOD = 20170805;

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
int solution(int m, int n, vector<vector<int>> city_map) {
    vector<vector<vector<int>>> K(m, vector<vector<int>>(n, vector<int>(2, 0)));

    K[0][0][0] = 1;
    K[0][0][1] = 1;

    for(int i = 1; i < m; ++i) {
    	int c = city_map[i][0];
    	if(c == 0) {
    		K[i][0][0] = 1;
    		K[i][0][1] = 1;
    	}
    	else if(c == 1) {
    		break;
    	} else if(c == 2) {
    		K[i][0][0] = 1;
    	}
    }

    for(int i = 1; i < n; ++i) {
    	int c = city_map[0][i];
    	if(c == 0) {
    		K[0][i][0] = 1;
    		K[0][i][1] = 1;
    	}
    	else if(c == 1) {
    		break;
    	} else if(c == 2) {
    		K[0][i][1] = 1;
    	}
    }

    for(int x = 1; x < m; ++x) {
    	for(int y = 1; y < n; ++y) {
    		if(city_map[x][y] == 1)
    			continue;

    		K[x][y][0] = K[x-1][y][0];
    		K[x][y][1] = K[x][y-1][1];

    		if(city_map[x][y] == 0) {
    			K[x][y][0] += K[x][y][1];
    			K[x][y][0] %= MOD;
    			K[x][y][1] = K[x][y][0];
    		}
    	}
    }

   	return K[m-1][n-1][0];
}