#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

int main(void)
{
	int N;
	cin >> N;
	vector< vector<int> > map(N, vector<int>(N));
	for(int i=0;i<N;++i) {
		string str;
		cin >> str;
		for(int j=0;j<N;++j) {
			map[i][j] = str[j] - '0';
		}
	}
	int guard_N;
	cin >> guard_N;
	vector< vector<int> > guard_state(N, vector<int>(guard_N, 0));
	for(int i=0;i<N;++i) {
		int gN;
		cin >> gN;
		for(int j=0;j<gN;++j) {
			int val; cin >> val;
			guard_state[i][val] = 1;
		}
	}
	vector< vector<int> > guardable(N, vector<int>(guard_N, 0));
	for(int i=0;i<N;++i) {
		int gN;
		cin >> gN;
		for(int j=0;j<gN;++j) {
			int val; cin >> val;
			guardable[i][val] = 1;
		}
	}
	int conflict = 0;
	for(int k=0;k<guard_N;++k) {
		for(int i=0;i<N-1;++i) {
			for(int j=i+1; j<N;++j) {
				if(map[i][j] == 0) continue;
				if(guard_state[i][k] == 1 && guard_state[j][k] == 0) {
					if(guardable[j][k] == 0) {
						++conflict;
					}
				} else if(guard_state[i][k] == 0 && guard_state[j][k] == 1) {
					if(guardable[i][k] == 0) {
						++conflict;
					}
				}
			}
		}
	}
	cout << conflict << endl;
}