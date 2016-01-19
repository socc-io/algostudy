#include <stdio.h>

#define SWAP_M(x,y,t) ((t)=(x),(x)=(y),(y)=(t))

int n, mcnt, moving[20];

void findMinMove(int *ans, int sum, int nextIdx,
                 int l, int r) {
    int next, nextsum;
    if (nextIdx == mcnt) {
        if ((*ans) > sum) (*ans) = sum;
        return;
    }
    next = moving[nextIdx];
    if (next < l) {
        nextsum = sum + (l - next);
        if (nextsum < (*ans)) findMinMove(ans, nextsum, nextIdx + 1, next, r);
    } else if (next > r) {
        nextsum = sum + (next - r);
        if (nextsum < (*ans)) findMinMove(ans, nextsum, nextIdx + 1, l, next);
    } else {
        nextsum = sum + (next - l);
        if (nextsum < (*ans)) findMinMove(ans, nextsum, nextIdx + 1, next, r);
        nextsum = sum + (r - next);
        if (nextsum < (*ans)) findMinMove(ans, nextsum, nextIdx + 1, l, next);
    }
}

int main(void) {
    int i, lopen, ropen, temp, ans;

    scanf("%d %d %d %d", &n, &lopen, &ropen, &mcnt);
    for (i=0; i<mcnt; i++) {
        scanf("%d", &moving[i]);
    }

    if (lopen > ropen) SWAP_M(lopen, ropen, temp);

    ans = 999999;
    findMinMove(&ans, 0, 0, lopen, ropen);
    printf("%d\n", ans);

    return 0;
}
