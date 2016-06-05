#include <stdio.h>

#define MAXN 500000
#define MAXH 100000000

typedef struct stack {
    int index;
    int height;
} node;

int main(void) {
    int tower[MAXN];
    node towerStack[MAXN];
    int i, j, sp = 0, n = 0;

    scanf("%d", &n);
    for (i=0; i<n; i++) {
        scanf("%d", &tower[i]);
    }
    
    towerStack[sp].index = 0;
    towerStack[sp++].height = MAXH;
    
    printf("0 ");
    for (i=1; i<n; i++) {
        if (tower[i-1] > tower[i]) {
            towerStack[sp].index = i;
            towerStack[sp++].height = tower[i-1];
            printf("%d ", i);
        } else {
            for (j=sp; j>0; j--) {
                if (towerStack[j].height > tower[i]) break;
            }
            printf("%d ", towerStack[j].index);
        }
    }

    return 0;
}
