#include <stdio.h>
#include <vector>

using namespace std;

#pragma warning(disable:4996)

int connection[40][40];
int num;
class Set {
public:
	int val[40];
	int index_val;
	Set() {
		for (int i = 0; i<40; ++i) {
			val[i] = 0;
		}
		index_val = 0;
	}
	void operator=(Set o) {
		for (int i = 0; i<40; ++i) {
			val[i] = o.val[i];
		}
		index_val = o.index_val;
	}
};
vector<Set> vSet;
int main(void)
{
	scanf("%d", &num);
	for (int i = 0; i < num; ++i) {
		for (int j = 0; j <= i; ++j) {
			scanf("%d", &connection[i][j]);
			connection[j][i] = connection[i][j];
		}
	}
	Set tmpset;
	tmpset.index_val = 1;
	for (int i = num-1; i>=0; --i) {
		tmpset.val[0] = i;
		vSet.push_back(tmpset);
	}
	bool enter[40];
	Set bestset;
	while (!(vSet.empty())) {
		Set nowset = *(vSet.rbegin());
		vSet.pop_back();
		bool isEnd = true;
		for (int i = 0; i<num; ++i) {
			enter[i] = true;
		}
		for (int i = 0; i<nowset.index_val; ++i) {
			enter[nowset.val[i]] = false;
		}
		for (int i = num-1; i>=0; --i) {
			if (enter[i]) {
				bool linked = true;
				for (int j = 0; j<nowset.index_val; ++j) {
					if (!(connection[i][nowset.val[j]])) {
						linked = false;
						break;
					}
				}
				if (linked) {
					nowset.val[nowset.index_val++] = i;
					vSet.push_back(nowset);
					nowset.index_val--;
					isEnd = false;
				}
			}
		}
		if (isEnd) {
			if (bestset.index_val < nowset.index_val) {
				bestset = nowset;
			}
		}
	}
	printf("%d\n", bestset.index_val);
	for (int i = 0; i<bestset.index_val; ++i) {
		printf("%d ", bestset.val[i]+1);
	}
	printf("\n");
	return 0;
}