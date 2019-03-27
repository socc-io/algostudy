/*
 * author: smilu97
 * description:
 *  algorithm solving of https://www.acmicpc.net/problem/1030
 */

#include <cstdio>

#ifndef ONLINE_JUDGE
#define DEBUG
#endif

int s, N, K;
int rb, re;

bool isblack(int val) { return rb <= val && val <= re; }

bool check(int a, int b)
{
    while (a || b) {
        if (isblack(a % N) && isblack(b % N)) return true;
        a /= N;
        b /= N;
    }
    return false;
}

int main(void)
{
    int R1, R2, C1, C2;
    scanf("%d%d%d%d%d%d%d", &s, &N, &K, &R1, &R2, &C1, &C2);
    rb = N/2 - K/2;
    re = N/2 + K/2 + (N & 1) - 1;
    for (int x = R1; x <= R2; x++) {
        for (int y = C1; y <= C2; y++) {
            printf("%c", check(x, y) ? '1' : '0');
        } puts("");
    }
    return 0;
}