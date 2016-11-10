#include <iostream>
using namespace std;

void squareprint(int **arr, int n)
{
	for(int i=0;i<n;++i) {
		for(int j=0;j<n;++j) {
			cout << arr[i][j] << "\t";
		}
		cout << endl;
	}
}

void magicsquare(int **arr, int n)
{
	int n2 = n * n;
	int curx = n / 2;
	int cury = 0;
	int next_x, next_y;
	int curval = 1;
	for(int i=0;i<n;++i)for(int j=0;j<n;++j)arr[i][j] = -1;
	for(int phase=0; phase<n2; ++phase)
	{
		arr[cury][curx] = curval++;
		next_x = curx + 1;
		next_y = cury - 1;
		if(next_x >= n) next_x = 0;
		if(next_y < 0) next_y = n-1;
		if(arr[next_y][next_x] == -1) {
			curx = next_x;
			cury = next_y;
		}
		else {
			++cury;
		}
	}
}

int main(void)
{
	int n;
	cin >> n;
	int **arr = new int*[n];
	for(int i=0;i<n;++i) arr[i] = new int[n];
	magicsquare(arr, n);
	squareprint(arr, n);
	for(int i=0;i<n;++i) delete[] arr[i];
	delete[] arr;
	return 0;
}