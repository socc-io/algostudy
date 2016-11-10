#include <iostream>

using namespace std;

#define INFINITE 999999

char check(int from, int to)
{
	if(to == from) {
		return 'O';
	}
	if(to == from + 1) {
		return 'A';
	}
	if(to == from - 1) {
		return 'C';
	}
	if(to == from*2) {
		return 'B';
	}
	return 'T';
}

int main(void){
	int N;
	int Tlimit;
	int tcnt = 0;
	cin >> N >> Tlimit;
	int **hole = new int*[N];
	int **mint = new int*[N];
	int *hole_num = new int[N];
	for(int i=0;i<N;++i) {
		cin >> hole_num[i];
		hole[i] = new int[hole_num[i]];
		mint[i] = new int[hole_num[i]];
		for(int j=0;j<hole_num[i];++j) {
			cin >> hole[i][j];
			mint[i][j] = INFINITE;
		}
	}
	for(int i=0;i<hole_num[0];++i) {
		char val = check(1, hole[0][i]);
		if(val == 'T') {
			mint[0][i] = 1;
		}
		else {
			mint[0][i] = 0;
		}
	}
	for(int i=1;i<N;++i) {
		int left_hole_num = hole_num[i-1];
		int right_hole_num = hole_num[i];
		for(int left=0; left<left_hole_num; ++left) {
			for(int right=0; right<right_hole_num;++right) {
				char val = check(hole[i-1][left], hole[i][right]);
				int newval = mint[i-1][left];
				if(val == 'T') {
					++newval;
				}
				if(newval < mint[i][right]) {
					mint[i][right] = newval;
				}
			}
		}
	}
	int min = mint[N-1][0];
	for(int i=1;i<hole_num[N-1];++i) {
		if(mint[N-1][i] < min) {
			min = mint[N-1][i];
		}
	}
	if(min > Tlimit) {
		cout << -1 << endl;
	}
	else {
		cout << min << endl;
	}

	for(int i=0;i<N;++i) {
		delete[] hole[i];
	}
	delete[] hole;
	delete[] hole_num;
}