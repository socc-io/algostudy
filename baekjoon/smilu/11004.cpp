#include<iostream>
using namespace std;

int arr[5000000];

void aswap(int a, int b)
{
    int tmp = arr[a];
    arr[a] = arr[b];
    arr[b] = tmp;
}

int findk(int start, int end, int k)
{
    // printf("start: %d, end: %d\n", start, end);
    int idx=start;
    for(int i=start; i<end-1; ++i) {
        if(arr[i] <= arr[end-1]) {
            aswap(i, idx++);
        }
    }
    aswap(idx, end-1);
    int lcnt = idx-start+1;
    if(k == lcnt) return arr[idx];
    if(k < lcnt) return findk(start, idx, k);
    return findk(idx+1, end, k-lcnt);
}
int main()
{
    int n, k;
    scanf("%d%d", &n, &k);
    for(int i=0; i<n; ++i) {
        scanf("%d", arr+i);
    }
    printf("%d", findk(0, n, k));
}
