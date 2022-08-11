#include <bits/stdc++.h>
using namespace std;

// 반시계 방향으로 돌았을 때 다음 방향
const int next_dir[5] = {-1, 4, 3, 1, 2};

int k;
int dir[6];
int len[6];

int main() {
    cin >> k;

    for (int i = 0; i < 6; i++) {
        cin >> dir[i] >> len[i];
    }

    int pivot; // 다음 코너에서 시계방향으로 도는 변은 무조건 하나
    for (int i = 0; i < 6; i++) {
        int ni = (i + 1) % 6;
        if (next_dir[dir[i]] != dir[ni]) { // 반시계 방향으로 돌지 않았음
            pivot = i;
            break;
        }
    }

    // 시계 방향으로 도는 코너와 맞닿는 두 변이 항상 안쪽으로 오목한 직사각형
    int concave = len[pivot] * len[(pivot + 1) % 6];

    int l1 = 0;
    for (int i = 0; i < 6; i += 2) {
        l1 = max(l1, len[i]);
    }

    int l2 = 0;
    for (int i = 1; i < 6; i += 2) {
        l2 = max(l2, len[i]);
    }

    int area = l1*l2 - concave;

    cout << area * k;
}
