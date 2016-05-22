#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define INFINITE 999999

int num;
int **dat;
int *connect;
int **colrank;
int *yCount;

void debugprint() {
	cout << "dat : " << endl;
	for (int i = 0; i < num; ++i) {
		for (int j = 0; j < num; ++j) {
			cout << dat[i][j] << " ";
		}
		cout << endl;
	}
	cout << "connect : " << endl;
	for (int i = 0; i < num; ++i) {
		cout << connect[i] << " ";
	}
	cout << endl;
	cout << "colrank : " << endl;
	for (int i = 0; i < num; ++i) {
		for (int j = 0; j < num; ++j) {
			cout << colrank[i][j] << " ";
		}
		cout << endl;
	}
	cout << "yCount : " << endl;
	for (int i = 0; i < num; ++i) {
		cout << yCount[i] << " ";
	}
	cout << endl;
}

int FindOverlapped() {
	for (int i = 0; i < num; ++i) {
		if (yCount[connect[i]] > 1) {
			return connect[i];
		}
	}
	return -1;
}
void Check(int oly) {
	vector<int> ox; // Overlap X
	for (int i = 0; i < num; ++i) {
		if (connect[i] == oly) {
			ox.push_back(i);
		}
	}
	int minX;
	int minValue = INFINITE;
	for (vector<int>::iterator it = ox.begin(); it != ox.end(); ++it) {
		if (minValue > dat[*it][oly]) {
			minValue = dat[*it][oly];
			minX = *it;
		}
	}
	for (int i = 0; i < num; ++i) {
		if (colrank[minX][i] == oly) continue;
		yCount[connect[minX]]--;
		connect[minX] = colrank[minX][i];
		yCount[connect[minX]]++;
		int bestValue = -1;
		int bestX;
		for (int j = 0; j < num; ++j) {
			if (connect[j] == colrank[minX][i]) {
				if (dat[j][colrank[minX][i]] > bestValue) {
					bestValue = dat[j][colrank[minX][i]];
					bestX = j;
				}
			}
		}
		if (bestX == minX) {
			break;
		}
	}
}

void Init() {
	for (int i = 0; i < num; ++i) {
		yCount[i] = 0;
	}
	for (int i = 0; i < num; ++i) {
		connect[i] = colrank[i][0];
		yCount[colrank[i][0]]++;
	}
}

void UpdateRank() {
	int *tmparr = new int[num];
	for (int i = 0; i < num; ++i) {
		for (int j = 0; j < num; ++j) {
			tmparr[j] = dat[i][j];
		}
		for (int j = 0; j < num; ++j) {
			int best = -1;
			int best_index = -1;
			for (int k = 0; k < num; ++k) {
				if (tmparr[k] > best) {
					best = tmparr[k];
					best_index = k;
				}
			}
			tmparr[best_index] = -1;
			colrank[i][j] = best_index;
		}
	}
	delete[] tmparr;
}

int main(void)
{
	cin >> num;
	dat = new int*[num];
	for (int i = 0; i < num; ++i) dat[i] = new int[num];
	colrank = new int*[num];
	for (int i = 0; i < num; ++i) colrank[i] = new int[num];
	yCount = new int[num];
	connect = new int[num];
	for (int i = 0; i < num; ++i) {
		for (int j = 0; j < num; ++j) {
			cin >> dat[i][j];
		}
	}
	UpdateRank();
	Init();
	int oly = FindOverlapped();
	while (oly != -1) {
		Check(oly);
		oly = FindOverlapped();
	}
	int sum = 0;
	for (int i = 0; i < num; ++i) {
		sum += dat[i][connect[i]];
	}
	debugprint();
	cout << sum << endl;
	for (int i = 0; i < num; ++i) {
		cout << connect[i] + 1 << " ";
	}
	cout << endl;
	for (int i = 0; i < num; ++i)delete[] dat[i];
	delete[] dat;
	delete[] yCount;
	delete[] connect;
	for (int i = 0; i < num; ++i) delete[] colrank[i];
	delete[] colrank;
	return 0;
}