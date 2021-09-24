#include <bits/stdc++.h>
using namespace std;

/**
 * 결과가 저장될 배열
 * 입력에서 0이 아닌 자리는 그대로 answer에 복사되며 DFS에서 나머지 부분을 처리하게 된다.
 */
int answer[9][9];

/**
 * 입력에서 0을 받았던 자리들을 모두 기록.
 * 이론상 81개의 0을 받을 수 있고, count_zero가 받았던 0의 개수를 세도록 한다.
 */
int pos_zero_x[81]; // position of zero . x
int pos_zero_y[81]; // position of zero . y
int count_zero;

/**
 * slot_row[x][v]는 x번째 줄에 v가 이미 사용되었는지 기록한다.
 * slot_col[y][v]는 y번째 열에 v가 이미 사용되었는지 기록한다.
 * slot_col[x/3][y/3][v]는 (x/3), (y/3)번째 3x3 블록에 v가 이미 사용되었는지 기록한다.
 */
bool slot_row[9][10];
bool slot_col[9][10];
bool slot_box[3][3][10];

/**
 * x, y자리에 v가 쓰였는지, 혹은 있던 숫자가 지워졌는지에 따라
 * slot_* 변수가 가져야 할 값을 업데이트 한다.
 */
void PutNumber(int x, int y, int v, bool alloc) {
    slot_row[x][v] = alloc;
    slot_col[y][v] = alloc;
    slot_box[x/3][y/3][v] = alloc;
}

/**
 * slot_* 변수들을 참조해서 (x, y)자리에 v가 사용돼도 괜찮은지 확인한다.
 */
bool CheckNumber(int x, int y, int v) {
    return slot_row[x][v] ||
           slot_col[y][v] ||
           slot_box[x/3][y/3][v];
}

bool DFS(int index) {
    // 더 이상 채울 자리가 없으면 true를 반환
    if (index >= count_zero) return true;

    // index번째 0이 어느 자리였는지 불러온다.
    int x = pos_zero_x[index], y = pos_zero_y[index];

    for (int v = 1; v <= 9; v++) {
        if (CheckNumber(x, y, v)) continue;
        PutNumber(x, y, v, true);
        if (DFS(index + 1)) {
            // 만약 0들이 모두 끝까지 채워졌다면 그 순간의 경과들을 answer에 기록하고 true를 반환
            answer[x][y] = v;
            return true;
        }
        PutNumber(x, y, v, false);
    }

    return false;
}

int main() {
    for (int x = 0; x < 9; x++) {
        for (int y = 0; y < 9; y++) {
            int v;
            scanf("%d", &v);
            if (v == 0) {
                /**
                 * 0을 입력으로 받았다면 그 자리들을 모두 순서대로 기록한다.
                 */
                pos_zero_x[count_zero] = x; 
                pos_zero_y[count_zero] = y;
                ++count_zero;
            } else {
                PutNumber(x, y, v, true);
                answer[x][y] = v;
            }
        }
    }
    DFS(0);
    for (int x = 0; x < 9; x++) {
        for (int y = 0; y < 9; y++) {
            printf("%d ", answer[x][y]);
        }
        puts("");
    }
}
