#include <stdio.h>
#pragma warning(disable:4996)
int spinset[9][6] = {
	{ 0, 1, 3, 4, -1, -1 },
	{ 0, 1, 2, -1, -1, -1 },
	{ 1, 2, 4, 5, -1, -1 },
	{ 0, 3, 6, -1, -1, -1 },
	{ 1, 3, 4, 5, 7, -1 },
	{ 2, 5, 8, -1, -1, -1 },
	{ 3, 4, 6, 7, -1, -1 },
	{ 6, 7, 8, -1, -1, -1 },
	{ 4, 5, 7, 8, -1, -1 }
};
bool isFindAnswer = false;
class clock {
public:
	int value;
	clock() {
		value = 0;
	}
	void spin() {
		++value;
		if (value == 4)value = 0;
	}
	void unspin() {
		--value;
		if (value == -1)value = 3;
	}
};
int mngf_dest_depth;
class Node {
public :
	clock clocks[9];
	Node *next[9];
	int setcount[9];
	Node *parent;
	int depth;
	int number;
	bool CheckIfComplete() {
		for (int i = 0; i < 9; ++i) {
			if (clocks[i].value != 0) return false;
		}
		return true;
	}
	void DoSet(int n) {
		for (int i = 0; spinset[n][i] != -1; ++i) {
			clocks[spinset[n][i]].spin();
		}
		setcount[n]++;
	}
	void MakeNextGenerationFlow() {
		if (depth == mngf_dest_depth) {
			for (int i = number; i < 9; ++i) {
				if (setcount[i] >= 3) continue;
				next[i] = new Node(this);
				next[i]->DoSet(i);
				next[i]->number = i;
				if (next[i]->CheckIfComplete()) {
					isFindAnswer = true;
					int *printer = new int[depth + 2];
					int index_printer = 0;
					Node *observer = next[i];
					while (observer->depth != 0) {
						printer[index_printer++] = observer->number;
						observer = observer->parent;
					}
					for (int i = index_printer - 1; i >= 0; --i) {
						printf("%d ", printer[i]+1);
					}
					printf("\n");
					delete[] printer;
				}
			}
		}
		else
		{
			for (int i = number; i < 9; ++i) {
				if (setcount[i] >= 3) continue;
				next[i]->MakeNextGenerationFlow();
				if (isFindAnswer) return;
			}
		}
	}
	Node() {
		for (int i = 0; i < 9; ++i) next[i] = 0;
		depth = 0;
		number = 0;
		for (int i = 0; i < 9; ++i) {
			setcount[i] = 0;
		}
	}
	Node(Node *pare) {
		for (int i = 0; i < 9; ++i) next[i] = 0;
		for (int i = 0; i < 9; ++i) {
			clocks[i] = pare->clocks[i];
		}
		for (int i = 0; i < 9; ++i) {
			setcount[i] = pare->setcount[i];
		}
		parent = pare;
		depth = pare->depth + 1;
	}
	~Node() {
		if (next[0] == 0)
			for (int i = 0; i < 9; ++i) {
				delete next[i];
			}
	}
};
Node first;

int main(void) {
	for (int i = 0; i < 9; ++i) {
		int tmp;
		scanf("%d", &tmp);
		switch (tmp) {
		case 12:
			first.clocks[i].value = 0;
			break;
		case 3:
			first.clocks[i].value = 1;
			break;
		case 6:
			first.clocks[i].value = 2;
			break;
		case 9:
			first.clocks[i].value = 3;
			break;
		default :
			printf("Input Error!\n");
		}
	}
	mngf_dest_depth = 0;
	while (!isFindAnswer) {
		// printf("Now Depth : %d\n", mngf_dest_depth);
		first.MakeNextGenerationFlow();
		++mngf_dest_depth;
	}
	return 0;
}