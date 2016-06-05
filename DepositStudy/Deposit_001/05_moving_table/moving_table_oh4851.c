#include <stdio.h>

#define USETIME 10

int main(void) {
    int i, j, moving, start, end, max;
    int s[200], t[200];
    int count[200] = {0, };
    
    scanf("%d", &moving);
    for (i=0; i<moving; i++) {
        scanf("%d %d", &s[i], &t[i]);
        s[i] = (s[i]-1)/2;
        t[i] = (t[i]-1)/2;
    }
    
    for (i=0; i<moving; i++) {
        if (s[i] < t[i]) {
            start = s[i];
            end = t[i];
        }
        else {
            start = t[i];
            end = s[i];
        }
        for (j=start; j<=end; j++) {
            count[j]++;
        }
    }
    
    max = count[0];
    for (i=1; i<200; i++) {
        if (count[i] > max) max = count[i];
    }
    
    printf("%d", max * USETIME);
}
