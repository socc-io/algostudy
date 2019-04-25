/*
 * author: smilu97
 * description:
 *   algorithm solving: https://www.acmicpc.net/problem/17140
 */

#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

typedef vector< vector<int> > vvi;

struct view {
    vvi * p_vec;
    int bx, by, dx, dy;
    view(vvi & mat): bx(0), by(0), dx(1), dy(0) {
        p_vec = &mat;
    }
    int& operator[](int idx) {
        return (*p_vec)[bx + dx * idx][by + dy * idx];
    }
};

template <class T>
int ant_sort(T & v)
{
    map<int, int> cnt;
    vector<pair<int,int>> pairs;
    for (int i = 0; i < 100; i++) {
        int val = v[i];
        if (val) cnt[val] += 1;
    }
    for (auto p: cnt)
        pairs.push_back(make_pair(p.second, p.first));
    sort(pairs.begin(), pairs.end());
    int len = 0;
    for (auto p: pairs) {
        v[len++] = p.second;
        v[len++] = p.first;
        if (len >= 100) break;
    }
    for (int i = len; i < 100; i++) v[i] = 0;
    return len;
}

int solve(int r, int c, int k, vvi & mat)
{
    view v(mat);
    int row = 3, col = 3;
    for (int i = 0; i <= 100; i++) {
        if (mat[r][c] == k) return i;
        if (row >= col) for (int i = 0; i < 100; i++) {
            int len = ant_sort(mat[i]);
            col = col < len ? len : col;
        } else for (int i = 0; i < 100; i++) {
            v.by = i;
            int len = ant_sort(v);
            row = row < len ? len : row;
        }
    }
    return -1;
}

int main(void)
{
    int r, c, k;
    scanf("%d%d%d", &r, &c, &k);

    vvi mat(100, vector<int>(100));
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            scanf("%d", &mat[i][j]);
        }
    }

    printf("%d\n", solve(r - 1, c - 1, k, mat));

    return 0;
}