#include <stdio.h>

int main(void) {
    int cost[] = {25, 10, 5, 1};
    char strCost[][16] = {"QUARTER(S)", "DIME(S)", "NICKEL(S)", "PENNY(S)"};
    int change = 0;
    int i;
    
    scanf("%d", &change);
    for (i=0; i<4; i++) {
        if (i == 3) printf("%d %s\n", change/cost[i], strCost[i]);
        else printf("%d %s, ", (change/cost[i]), strCost[i]);
        change = change%cost[i];
    }
    printf("\n");

    return 0;
}
