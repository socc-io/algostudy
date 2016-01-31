#include <iostream>
using namespace std;

int grid[9][9]; // 스도쿠 행렬

bool CheckClear(int &row,int &col) { // 만약에 아직 0인 구간이 있으면 덜 끝난것

	for (row = 0; row < 9; row++)
		for (col = 0; col < 9; col++)
			if (grid[row][col] == 0)
				return true;

	return false;

}

bool CheckCol(int col, int num) // 열체크
{
	for (int row = 0; row < 9; row++)
		if (grid[row][col] == num)
			return true;
	return false;
}

bool CheckRow(int row, int num) // 행체크
{
	for (int col = 0; col < 9; col++)
		if (grid[row][col] == num)
			return true;
	return false;
}

bool CheckBox(int Start_row,int Start_col, int num) // 3 * 3 구간 체크
{
	for (int row = 0; row < 3; row++)
		for (int col = 0; col < 3; col++)
			if (grid[row + Start_row][col + Start_col] == num)
				return true;

	return false;

}


bool IsSudoku() {

	int row, col;

	if (!CheckClear(row, col)) // 더 이상 체크된게 0이 없으면
		return true; 

	for (int i = 1; i <= 9; i++)
	{
		if (CheckRow(row, i) && CheckCol(col, i) && CheckBox(row - row % 3, col - col % 3, i)); // 넣었던 숫자가 조건에 다 만족하면
		{
			grid[row][col] = i; // i를 그 행과 열에 해당하는 부분에 넣음

			if (IsSudoku())
				return true;

			grid[row][col] = 0; // 만약 다음번에 들어갈 부분이 스도쿠 조건에 만족하지 않으면 다시 0으로 초기화

		}
	}
	return false;

}


void PrintSudoku() {

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++) {
			cout << grid[i][j] << " ";
		}

		cout << endl;
	}
}


int main()
{
	int num;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			cin >> num;
			grid[i][j] = num;
		}

	}

	if (IsSudoku() == true)
		PrintSudoku();

	return  0;

}