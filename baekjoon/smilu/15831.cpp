#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 300000;

int N, B, W;
char tile[MAX_N + 30];

int c_start, c_end, c_white, c_black;
int max_length;

bool validate() {
    return c_black <= B && c_white >= W;
}

void capture() {
    if (validate()) {
        // printf("capture: %d, %d\n", c_start, c_end);
        max_length = max(max_length, c_end - c_start);
    }
}

void pick(int i, int v) {
    if (tile[i] == 'W') c_white += v;
    else c_black += v;
}

void push_forward() {
    assert(c_end < N);
    pick(c_end++, 1);
}

void revert_push_forward() {
    pick(--c_end, -1);
}

void pop_forward() {
    assert(c_start < c_end);
    pick(c_start++, -1);
}

int solve() {
    while (c_end < N) {
        while (c_white < W && c_end < N) push_forward();
        while (c_end < N && tile[c_end] == 'W') push_forward();
        while (c_end < N) {
            push_forward();
            if (c_black > B) {
                revert_push_forward();
                break;
            }
        }
        while (c_black > B) pop_forward();
        capture();
        if (c_start < c_end) pop_forward();
        else if (c_end < N) push_forward();
    }
    return max_length;
}

int main(void)
{
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N >> B >> W >> tile;
    printf("%d\n", solve());
}
