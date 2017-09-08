#include<iostream>
#include<vector>

using namespace std;

int n;
bool tile[100][100];

int main(void)
{
    scanf("%d", &n);
    for(int i=0; i<n; ++i) {
        getchar();
        for(int j=0; j<n; ++j) {
            if(getchar() == '.') tile[i][j] = false;
            else tile[i][j] = true;
        }
    }
    int vert_cnt=0;
    for(int y=0; y<n; ++y) {
        int cnt=0;
        for(int x=0; x<n; ++x) {
            if(tile[x][y] == false) {
                ++cnt;
                if(cnt == 2) ++vert_cnt;
            }
            else cnt = 0;
        }
    }
    int hori_cnt=0;
    for(int x=0; x<n; ++x) {
        int cnt=0;
        for(int y=0; y<n; ++y) {
            if(tile[x][y] == false) {
                ++cnt;
                if(cnt == 2) ++hori_cnt;
            }
            else cnt = 0;
        }
    }
    printf("%d %d", hori_cnt, vert_cnt);
}
            
