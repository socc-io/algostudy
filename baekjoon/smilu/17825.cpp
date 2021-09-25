#include <bits/stdc++.h>
using namespace std;

int dices[10];
int units[4];
bool is_full[50];

int red_conn[50];
int blue_conn[50];
int tile_score[50];

void Setup() {
    for (int i = 0; i < 20; i++) {
        red_conn[i] = i+1;
        tile_score[i] = i<<1;
    }
    red_conn[21] = 22; tile_score[21] = 13;
    red_conn[22] = 23; tile_score[22] = 16;
    red_conn[23] = 29; tile_score[23] = 19;
    red_conn[24] = 25; tile_score[24] = 22;
    red_conn[25] = 29; tile_score[25] = 24;
    red_conn[26] = 27; tile_score[26] = 28;
    red_conn[27] = 28; tile_score[27] = 27;
    red_conn[28] = 29; tile_score[28] = 26;
    red_conn[29] = 30; tile_score[29] = 25;
    red_conn[30] = 31; tile_score[30] = 30;
    red_conn[31] = 20; tile_score[31] = 35;
    red_conn[20] = 41; tile_score[20] = 40;
    blue_conn[5] = 21;
    blue_conn[10] = 24;
    blue_conn[15] = 26;
}

int Traverse(int x, int distance) {
    if (distance <= 0) return x;
    if (blue_conn[x]) {
        x = blue_conn[x];
        --distance;
    }
    while (distance-- && x != 41)
        x = red_conn[x];
    return x;
}

int DFS(int level) {
    if (level >= 10) return 0;

    const int distance = dices[level];
    const int next_level = level + 1;
    int max_score = 0;

    for (int i = 0; i < 4; i++) { // i: unit index
        const int src = units[i];
        if (src == 41) continue;

        const int dest = Traverse(src, distance);
        if (0 < dest && dest <= 40 && is_full[dest]) continue;

        is_full[src] = false;
        is_full[dest] = true;
        units[i] = dest;

        max_score = max(max_score, DFS(next_level) + tile_score[dest]);

        units[i] = src;
        is_full[dest] = false;
        is_full[src] = true;
    }

    return max_score;
}

int main() {
    Setup();
    for (int i = 0; i < 10; i++) scanf("%d", &dices[i]);
    printf("%d\n", DFS(0));
}
