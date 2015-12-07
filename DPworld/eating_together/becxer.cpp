#include <iostream>

using namespace std;

int min_seq[30001][4];
int max_seq[30001][4];

int main(void){
	int N, now;
	cin >> N;
	for (int i = 1; i < 4; i++){
		min_seq[0][i] = 1;
		max_seq[0][i] = 1;
	}
	cin >> now;
	min_seq[0][now] = 0;
	max_seq[0][now] = 0;

	for (int i = 1; i < N; i++){
		cin >> now;
		for (int change = 1; change < 4; change ++){
			min_seq[i][change] = 99999;
			max_seq[i][change] = 99999;
			for (int past = 1; past < 4; past++){
				if (min_seq[i][change] >= min_seq[i - 1][past] && change >= past){
					min_seq[i][change] = min_seq[i - 1][past];
				}
				
				if (max_seq[i][change] >= max_seq[i - 1][past] && change <= past){
					max_seq[i][change] = max_seq[i - 1][past];
				}
			}
			if (change != now){
				min_seq[i][change] += 1;
				max_seq[i][change] += 1;
			}
		}
	}
	
	int most_min = 99999;
	for (int i = 1; i < 4; i++){
		if (most_min >= min_seq[N - 1][i]) most_min = min_seq[N - 1][i];
		if (most_min >= max_seq[N - 1][i]) most_min = max_seq[N - 1][i];
	}
	cout << most_min << endl;
	return 0;
}
