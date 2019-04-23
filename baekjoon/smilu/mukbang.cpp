/*
 * author: smilu97
 * description:
 *   algorithm solving: https://www.welcomekakao.com/learn/courses/30/lessons/42891
 */

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long lld;

void print_vecint(vector<int>& vec) {
    for (int val: vec) printf("%d ", val); puts("");
}

int solution(vector<int> food_times, lld k) {
    vector<int> arr(food_times);
    sort(arr.begin(), arr.end());
    int len = arr.size();
    lld cur = 0;
    lld height = 0;

    while (cur < len) {
        lld area = (arr[cur] - height) * (len - cur);
        if (area <= k) {
            k -= area;
            height = arr[cur];
            while (arr[cur] == height && cur < len) cur++;
        } else break;
    }

    if (cur == len) return -1;

    k %= len - cur;
    for (int i = 0, j = 0; i < len; i++) {
        if (food_times[i] <= height) continue;
        if (j == k) {
            return i + 1;
        }
        j++;
    }

    return -1;
}

int main(void)
{
    vector<int> food_times = {3, 1, 2};
    int answer = solution(food_times, 5);
    printf("ans: %d\n", answer);
}