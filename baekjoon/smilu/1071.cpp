/*
*
* Author: smilu97 (smilup2244@gmail.com)
*
* Idea: DFS to find sequence satisfacting all conditions
*   the key point was preventing duplication of calculation
*   by memoization to prevent travel node that have same value of
*   other node that already traveled
*
* Checked in Baekjoon (https://www.acmicpc.net/problem/1071) in 170721
*   Mem: 1116KB, Time: 0ms, Lang: C++14
*   Scoring number: #6291623
*
*/


#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int N;
int arr[50];
bool in_use[50];
int ans[50];

bool calc(int pos)
{
	if(pos == N) {  // end of travel
		return true;
	}

	int prev = -1;  // memo to prevent duplication of calculation
	for(int i = 0; i < N; ++i) {

		if(in_use[i])  // prevent duplication of using
			continue;

		if(pos > 0 && (ans[pos - 1] + 1 == arr[i]))  // arr[i] + 1 != arr[i + 1]
			continue;

		if(prev == arr[i])  // prevent duplication of calculation
			continue;

		// travel
		ans[pos] = arr[i];
		in_use[i] = true;

		if(calc(pos + 1)) {
			return true;
		}

		// travel fail
		in_use[i] = false;

		prev = arr[i];  // memo the number already traveled
	}

	return false;
}

int main(void)
{
	int i, j;

	freopen("input.txt", "r", stdin);

	while(~scanf("%d", &N))
	{
		// input
		for(i = 0; i < N; ++i) {
			scanf("%d", arr + i);
		}

		sort(arr, arr + N);

		memset(in_use, false, sizeof(in_use));

		calc(0);

		for(int i = 0; i < N; ++i) {
			printf("%d ", ans[i]);
		} printf("\n");
	}
}