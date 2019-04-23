/*
 * author: smilu97
 * description:
 *   algorithm solving of https://www.acmicpc.net/problem/1032
 */

#include <cstdio>
#include <cstring>

int N;
char strs[50][51];
char ans[51];
int len;

int main(void)
{
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%50s", strs[i]);
    }
    len = strlen(strs[0]);
    
    for (int i = 0; i < len; i++) {
        bool same = true;
        char ch = strs[0][i];
        for (int j = 1; j < N; j++) {
            if (strs[j][i] != ch) {
                same = false;
                break;
            }
        }
        ans[i] = same ? ch : '?';
    }
    printf("%s\n", ans);

    return 0;
}