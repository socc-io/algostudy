#include <iostream>
#include <algorithm>
using namespace std;

int cnt;

int compare(const void * a, const void * b)
{
	return (*(int*)a - *(int*)b);
}

void UtilGetNumber(int _jurely_num, int _mid, int start, int _jurely[], int sum)
{
	for (int j = start; j < _jurely_num; j++) {
		if (_jurely[j] + sum > _mid)
			break;

		else if (_jurely[j] + sum == _mid)
			cnt++;
		else
			UtilGetNumber(_jurely_num, _mid, j + 1, _jurely, _jurely[j] + sum);
	}

}

void GetNumber(int jurely_num, int jurely[], int jurely_sum)
{
	int sum = 0;
	int mid_sum = jurely_sum / 2;

	UtilGetNumber(jurely_num, mid_sum, 0, jurely, sum);


	cout << cnt;

}

int main()
{
	int jurely_num;
	int jurely_weight[31];
	int jurely_sum = 0;
	cnt = 0;
	cin >> jurely_num;

	for (int i = 0; i < jurely_num; i++)
	{
		int num;
		cin >> num;
		jurely_weight[i] = num;
		jurely_sum += num;
	}

	qsort(jurely_weight, jurely_num, sizeof(int), compare);

	if (jurely_sum % 2 != 0)
		cout << "impossible";
	else
		GetNumber(jurely_num, jurely_weight, jurely_sum);

	return 0;


}