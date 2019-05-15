/*
 * author: smilu97
 * description:
 *   algorithm solving: https://www.acmicpc.net/problem/11004
 */

#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
 
int find_kth(vector<int> & arr, int K)
{
    nth_element(
        arr.begin(),
        arr.begin() + (K - 1),
        arr.end()
    );
    return arr[K - 1];
}

int main(void)
{
    int N, K;

    scanf("%d%d", &N, &K);
    vector<int> arr(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &arr[i]);
    }

    printf("%d", find_kth(arr, K));

    return 0;
}
