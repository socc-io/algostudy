#include <iostream>
#include <math.h>
using namespace std;

// 열체크를 한다
// 퀸을 배치할때마다 기존에 있던 퀸이랑 크래쉬가 안나는지 체크해야됨
// 모든 열에 퀸이 하나씩 있다 -> true
int num;
int _result[14];
int _count = 0;

// y2 -> 현재 열에 같은것이 있던가.

bool isSafe(int row, int col)
{
	for (int i = 0; i < row; i++)
	{
		if ((_result[i] == col) || (abs(i - row) == abs(_result[i] - col)))
			return false;
	}
	return true;
}

void solveUtil(int x, int size)
{
	for (int i = 0; i < size; i++) {
		if (isSafe(x, i))
		{
			_result[x] = i;
			if (x == size - 1)
			{
				if (_count < 3)
				{
					for (int j = 0; j < size; j++)
					{
						cout << _result[j] + 1 << " ";
					}
					cout << endl;
				}
				_count++;
				
			}
			solveUtil(x + 1, size);
		}
	}
	
}

int main()
{
	cin >> num;
	solveUtil(0, num);
	cout << _count;

}