#include <stdio.h>

int main(void) {
    int i, j, temp, sum;
    int nums[5];

    sum = 0;
    for (i=0; i<5; i++) {
        scanf("%d", &nums[i]);
        sum += nums[i];
    }
    for (i=1; i<5; i++) {
        temp = nums[i];
        j = i-1;
        while ((j >= 0) && (nums[j] > temp)) {
            nums[j+1] = nums[j];
            j--;
        }
        nums[j+1] = temp;
    }
    
    printf("%d\n", sum / 5);
    printf("%d\n", nums[2]);
}
