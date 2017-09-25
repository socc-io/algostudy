#include <vector>
#include <queue>

using namespace std;

const int dir[4][2] = {1, 0, -1, 0, 0, 1, 0, -1};

int area[100][100];
int M, N;

int explore(int x, int y, int a, vector<vector<int>> &picture)
{
    int p = picture[x][y];

    if(p == 0) return 0;
    if(area[x][y] != -1) return 0;

    area[x][y] = a;
    int res = 1;

    for(int i = 0; i < 4; ++i) {
        int nx = x + dir[i][0], ny = y + dir[i][1];
        if(nx < 0 || nx >= M || ny < 0 || ny >= N) continue;
        if(picture[nx][ny] != p) continue;
        res += explore(nx, ny, a, picture);
    }

    return res;
}

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
vector<int> solution(int m, int n, vector<vector<int>> picture) {
    int area_num = 0;
    int max_size = 0;

    M = m;
    N = n;

    for(int i = 0; i < m; ++i) for(int j = 0; j < n; ++j) {
        area[i][j] = -1;
    }

    for(int x = 0; x < m; ++x) {
        for(int y = 0; y < n; ++y) {
            int size = explore(x, y, area_num, picture);
            if(size != 0) {
                area_num++;
                if(size > max_size) {
                    max_size = size;
                }
            }
        }
    }

    vector<int> ans(2);
    ans[0] = area_num;
    ans[1] = max_size;

    return ans;
}

int main(void)
{

}