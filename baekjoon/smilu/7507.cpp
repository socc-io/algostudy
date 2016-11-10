#include <stdio.h>
#include <stdlib.h>

#pragma warning(disable:4996)

class Plan
{
public:
	int day;
	int start;
	int end;
	int maxview;
public:
	void getInput() {
		scanf("%d%d%d", &day, &start, &end);
		int day_Add = day * 10000;
		start += day_Add;
		end += day_Add;
	}
	int compare(Plan* other)
	{
		if (start > other->start) return 1;
		else if (start < other->start) return -1;
		return 0;
	}
};

void planSort(Plan **arr, int size)
{
	int i, j, k;
	if (size < 8) {
		for (i = 1; i<size; ++i) {
			Plan *cur = arr[i];
			for (j = i - 1; j >= 0 && arr[j]->compare(cur) >= 0; --j) {
				arr[j + 1] = arr[j];
			}
			arr[j + 1] = cur;
		}
		return;
	}
	int p = size / 2;
	planSort(arr, p);
	planSort(arr + p, size - p);
	Plan **s = (Plan**)malloc(size*sizeof(Plan*));
	for (i = 0, j = p, k = 0; i<p && j<size;) {
		s[k++] = arr[i]->compare(arr[j]) == 1 ? arr[j++] : arr[i++];
	}
	while (i<p) s[k++] = arr[i++];
	while (j<size) s[k++] = arr[j++];
	for (i = 0; i<size; ++i) arr[i] = s[i];
	free(s);
}

int main(int argc, char **argv) {
	Plan buffer[50000];
	Plan *plan[50000];
	int T, m, maxview;
	scanf("%d", &T);
	for (int test_idx = 1; test_idx <= T; ++test_idx) {
		scanf("%d", &m);
		for (int i = 0; i<m; ++i) {
			plan[i] = &buffer[i];
			plan[i]->getInput();
		}
		planSort(plan, m);
		maxview = 0;
		int proceed = 0;
		while(proceed < m)
		{
			int nowstart = plan[proceed]->start;
			int nowend = plan[proceed]->end;
			int cur = proceed + 1;
			while(true)
			{
				if(cur >= m) {
					++maxview;
					break;
				}
				int curstart = plan[cur]->start;
				if(nowend <= curstart) {
					++maxview;
					break;
				}
				int curend = plan[cur]->end;
				if(curend < nowend) {
					nowstart = curstart;
					nowend = curend;
				}
				++cur;
			}
			proceed = cur;
		}
		printf("Scenario #%d:\n%d\n\n", test_idx, maxview);
	}

	return 0;
}