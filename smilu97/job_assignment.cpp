#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define INFINITE 999999
#define FREE -1

int cost[30][30];
bool tight[30][30];
int matching[30][30];
int x_y[30];
int y_x[30];
int labelx[30];
int labely[30];
int n;
int matchnum;
bool S[30];
bool T[30];
bool NlS[30];

int max_matchnum;
int max_x_y[30];
int max_y_x[30];
void DFS_Getmatching(int index)
{
	if (index == n) {
		if (matchnum > max_matchnum) {
			max_matchnum = matchnum;
			for (int i = 0; i < n; ++i) {
				max_x_y[i] = x_y[i];
				max_y_x[i] = y_x[i];
			}
		}
		return;
	}
	bool matched = false;
	for (int i = 0; i < n; ++i) {
		if (tight[index][i] == true && y_x[i] == FREE) {
			matched = true;
			x_y[index] = i;
			y_x[i] = index;
			++matchnum;
			DFS_Getmatching(index + 1);
			--matchnum;
			x_y[index] = FREE;
			y_x[i] = FREE;
		}
	}
	if (!matched) {
		DFS_Getmatching(index + 1);
	}
}

void Getmatching()
{
	for (int i = 0; i < n; ++i) {
		x_y[i] = FREE;
	}
	for (int i = 0; i < n; ++i) {
		y_x[i] = FREE;
	}
	matchnum = 0;
	max_matchnum = -1;
	DFS_Getmatching(0);
	for (int i = 0; i < n; ++i) {
		x_y[i] = max_x_y[i];
		y_x[i] = max_y_x[i];
	}
	matchnum = max_matchnum;
}

void SetTight()
{
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (labelx[i] + labely[j] == cost[i][j]) {
				tight[i][j] = true;
			}
			else {
				tight[i][j] = false;
			}
		}
	}
}

int Step1()
{
	SetTight();
	Getmatching();
	return 2;
}
int Step2()
{
	if (matchnum == n) return -1;
	for (int i = 0; i < n; ++i) {
		S[i] = false;
		T[i] = false;
		NlS[i] = false;
	}
	for (int i = 0; i < n; ++i) {
		if (x_y[i] == FREE) {
			S[i] = true;
			for (int j = 0; j < n; ++j) {
				if (tight[i][j] == true) {
					NlS[j] = true;
				}
			}
			break;
		}
	}
	return 3;
}
int Step3()
{
	bool nlsequalt = true;
	for (int i = 0; i < n; ++i) {
		if (NlS[i] != T[i]) {
			nlsequalt = false;
			break;
		}
	}
	if (nlsequalt) {
		// Update Label
		int amin = INFINITE;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				if (S[i] == true && T[j] == false) {
					int delta = labelx[i] + labely[j] - cost[i][j];
					if (amin > delta) {
						amin = delta;
					}
				}
			}
		}
		for (int i = 0; i < n; ++i) {
			if (S[i] == true) {
				labelx[i] -= amin;
			}
			if (T[i] == true) {
				labely[i] += amin;
			}
		}
		return 1;
	}
	else {
		return 4;
	}
}
int Step4()
{
	int y = -1;
	for (int i = 0; i < n; ++i) {
		if (NlS[i] == true && T[i] == false) {
			y = i;
			break;
		}
	}
	if (y_x[y] == FREE) {
		cout << "??" << endl;
	}
	else {
		int z = y_x[y];
		S[z] = true;
		for (int i = 0; i < n; ++i) {
			if (tight[z][i] == true) {
				NlS[i] = true;
			}
		}
		T[y] = true;
		return 3;
	}
}

void Hungarian()
{
	int step = 1;
	while (step != -1) {
		switch (step) {
		case 1:
			step = Step1();
			break;
		case 2:
			step = Step2();
			break;
		case 3:
			step = Step3();
			break;
		case 4:
			step = Step4();
			break;
		}
	}
}

int main(void)
{
	cin >> n;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			cin >> cost[i][j];
		}
	}
	for (int i = 0; i < n; ++i) { // Init label value
		int max = -1;
		for (int j = 0; j < n; ++j) {
			if (max < cost[i][j]) {
				max = cost[i][j];
			}
		}
		labelx[i] = max;
		labely[i] = 0;
	}
	Hungarian();
	int sum = 0;
	for (int i = 0; i < n; ++i) {
		sum += cost[i][x_y[i]];
	}
	cout << sum << endl;
	for (int i = 0; i < n; ++i) {
		cout << x_y[i] + 1 << " ";
	}
	cout << endl;
	return 0;
}