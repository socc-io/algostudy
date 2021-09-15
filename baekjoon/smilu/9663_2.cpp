#include <bits/stdc++.h>
using namespace std;

int n, answer;

bool selected_col[15];
bool selected_rb[30]; // 오른쪽 아래로 향하는 대각선 (right bottom => rb)
bool selected_lb[30]; // 왼쪽 아래로 향하는 대각선 (left bottom => lb)

/**
 * 놓여진 퀸들이 서로 공격할 수 없으려면,
 * 모든 퀸들의 좌표들의 y값들이 모두 달라야 하며
 * 좌표들의 x-y값들이 모두 달라야 하며
 * 좌표들의 x+y값들이 모두 달라야 한다.
 */
void PutOrRemoveQueen(int x, int y, bool put) {
    selected_col[y] = put;
    selected_rb[x-y+15] = put; // x-y는 최소 -13까지 작아질 수 있는데, 음수 인덱스를 포함할 수 없으므로 적당히 큰 수를 더해준다.
    selected_lb[x+y] = put;
}

bool CheckPosition(int x, int y) {
    return selected_col[y] ||
           selected_rb[x-y+15] ||
           selected_lb[x+y];
}

/**
 * 각 DFS 호출은 해당 x줄의 어느 column에 퀸이 놓일 수 있는지 확인한다.
 * 이 때 x보다 작은 row들에는 한 개씩 이미 퀸이 놓여있다.
 */
void DFS(int x) {
    if (x >= n) {
        ++answer;
        return;
    }

    for (int y = 0; y < n; y++) {
        if (CheckPosition(x, y)) continue;
        PutOrRemoveQueen(x, y, true);
        DFS(x + 1);
        PutOrRemoveQueen(x, y, false);
    }
}


int main() {
    scanf("%d", &n);
    DFS(0);
    printf("%d\n", answer);
    return 0;
}
