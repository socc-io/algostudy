/*
 * author: smilu97
 * description:
 *   algorithm solving of https://www.acmicpc.net/problem/1031
 */

#include <cstdio>
#include <vector>
using namespace std;

int N, M;
int pa[50], pb[50];
bool matched[50][50];
int visited[50];
int visit_idx;

bool match(int ai)
{
    visited[ai] = visit_idx;
    for (int bi = 0; bi < M; bi++) {
        if (matched[ai][bi]) continue;
        if (pb[bi]) {
            matched[ai][bi] = true;
            pb[bi]--;
            return true;
        }
        for (int ci = 0; ci < N; ci++) {
            if (!matched[ci][bi]) continue;
            if (visited[ci] == visit_idx) continue;
            if (match(ci)) {
                matched[ci][bi] = false;
                matched[ai][bi] = true;
                return true;
            }
        }
    }
    return false;
}

bool cycle(int cur, int des, pair<int, int> lower)
{
    visited[cur] = visit_idx;
    for (int bi = 0; bi < M; bi++) {
        if (matched[cur][bi]) continue;
        if (make_pair(cur, bi) <= lower) continue;
        if (bi == des) {
            matched[cur][bi] = true;
            return true;
        }
        for (int ci = 0; ci < N; ci++) {
            if (!matched[ci][bi]) continue;
            if (make_pair(ci, bi) <= lower) continue;
            if (visited[ci] == visit_idx) continue;
            if (cycle(ci, des, lower)) {
                matched[ci][bi] = false;
                matched[cur][bi] = true;
                return true;
            }
        }
    }
    return false;
}

int main(void)
{
    int sum_pa = 0;
    int sum_pb = 0;

    scanf("%d%d", &N, &M);
    for (int i = 0; i < N; i++) {
        scanf("%d", pa + i);
        sum_pa += pa[i];
    }
    for (int i = 0; i < M; i++) {
        scanf("%d", pb + i);
        sum_pb += pb[i];
    }
    if (sum_pa != sum_pb) {
        puts("-1");
        return 0;
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < pa[i]; j++) {
            visit_idx++;
            if (!match(i)) {
                puts("-1");
                return 0;
            }
        }
    }
    for (int i = 0; i < M; i++) {
        if (pb[i]) {
            puts("-1");
            return 0;
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (!matched[i][j]) continue;
            visit_idx++;
            if (cycle(i, j, make_pair(i, j))) {
                matched[i][j] = 0;
            }
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("%c", matched[i][j] ? '1' : '0');
        } puts("");
    }

    return 0;
}