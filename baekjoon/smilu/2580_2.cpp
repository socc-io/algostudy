#include <bits/stdc++.h>
using namespace std;

int answer[9][9];

int pos_zero_x[81];
int pos_zero_y[81];
int count_zero;

bool slot_row[9][10];
bool slot_col[9][10];
bool slot_box[3][3][10];

void PutNumber(int x, int y, int v, bool alloc) {
    slot_row[x][v] = alloc;
    slot_col[y][v] = alloc;
    slot_box[x/3][y/3][v] = alloc;
}

bool CheckNumber(int x, int y, int v) {
    return slot_row[x][v] ||
           slot_col[y][v] ||
           slot_box[x/3][y/3][v];
}

bool DFS(int index) {
    if (index >= count_zero) return true;
    int x = pos_zero_x[index], y = pos_zero_y[index];
    for (int v = 1; v <= 9; v++) {
        if (CheckNumber(x, y, v)) continue;
        PutNumber(x, y, v, true);
        answer[x][y] = v;
        if (DFS(index + 1)) return true;
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
