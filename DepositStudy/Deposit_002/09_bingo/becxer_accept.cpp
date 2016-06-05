#include <iostream>
#include <fstream>

using namespace std;


int map[6][6];
int bingo(){
	int count = 0;
	for (int i = 0; i < 5; i++) {
		int temp_x = 0;
		for (int j = 0; j < 5; j++){
			temp_x += map[i][j];
		}
		if (temp_x == 0) count++;
	}

	for (int i = 0; i < 5; i++) {
		int temp_y = 0;
		for (int j = 0; j < 5; j++){
			temp_y += map[j][i];
		}
		if (temp_y == 0) count++;
	}

	int temp_r = 0;
	for (int i = 0; i < 5; i++) {
		temp_r += map[i][i];
	}
	if (temp_r == 0) count++;

	int temp_l = 0;
	for (int i = 0; i < 5; i++) {
		temp_l += map[i][4-i];
	}
	if (temp_l == 0) count++;
	return count;
}

int solution(istream& in) {
	
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++){
			in >> map[i][j];
		}
	}

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++){
			int k;
			in >> k;
			for (int p = 0; p < 5; p++) {
				for (int q = 0; q < 5; q++){
					if (k == map[p][q]){
						map[p][q] = 0;
						break;
					}
				}
			}
			if (bingo() >= 3) {
				cout << 5*i + j+1 << endl;
				return 0;
			};
		}
	}

	return 0;
}

int main(void){
	ifstream ifs;
	ifs.open("input.input");
	return solution(*(&ifs));
}
