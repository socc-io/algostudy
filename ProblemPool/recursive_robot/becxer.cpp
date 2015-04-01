#include <iostream>

using namespace std;

int row, col, start;
char map[100][100];
int flag[100][100];

int get_dx(char a){
	switch (a){
		case 'N':
			return -1;
		case 'S':
			return 1;
		default:
			return 0;
	}
}

int get_dy(char a){
	switch (a){
	case 'W':
		return -1;
	case 'E':
		return 1;
	default:
		return 0;
	}
}

bool visit(int x,int y,int count){
	count++;
	if (x < 0 || y < 0 || x >= row || y >= col){
		cout << count << " step(s) to exit" << endl;
		return true;
	}
	else if (flag[x][y]!=-1){
		cout << flag[x][y] << " step(s) before a loop of " << count-flag[x][y] << " step(s)" << endl;
		return false;
	}else{
		flag[x][y] = count;
		int dx = x + get_dx(map[x][y]);
		int dy = y + get_dy(map[x][y]);
		visit(dx, dy, count);
	}
}

int main(void){
	cin >> row >> col >> start;
	for (int i = 0; i < row; i++){
		for (int j = 0; j < col; j++){
			cin >> map[i][j];
			flag[i][j] = -1;
		}
	}
	visit(0, start-1, -1);
	return 0;
}
