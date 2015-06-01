#include <stdio.h>

int main(void) {
    int i, min, minval;
    int card = 0;
    int cards[10] = {};
    int gin = 0;

    for (i=0; i<6; i++) {
        scanf("%d", &card);
        cards[card]++;
    }
    // find tripletes
    for (i=0; i<10; i++) {
        if (cards[i] >= 3) {
            gin += cards[i]/3;
            cards[i] -= gin*3;
        }
    }
    
    // find runs
    i = 0;
    while (i < 8) {
        if (cards[i] > 0 && cards[i+1] > 0 && cards[i+2] > 0) {
            min = i;
            if (cards[i+1] < cards[min]) min = i+1;
            if (cards[i+2] < cards[min]) min = i+2;

            minval = cards[min];
            gin += minval;
            cards[i] -= minval;
            cards[i+1] -= minval;
            cards[i+2] -= minval;
        }
        else {
            i++;
        }
    }

    // show result
    if (gin == 2) printf("gin\n");
    else printf("lose\n");
    printf("\n");

    return 0;
}
