#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int maxMoney[3][101];
int moneyOnRoad[101];
int numMoney;

int max3int(int a, int b, int c)
{
	if (a > b && a > c) return a;
	else if (b > a && b > c) return b;
	return c;
}

void setMaxMoney(int index)
{
	int previndex = index - 1;
	maxMoney[0][index] = max3int(maxMoney[0][previndex], maxMoney[1][previndex], maxMoney[2][previndex]);
	maxMoney[1][index] = maxMoney[0][previndex] + moneyOnRoad[index];
	maxMoney[2][index] = maxMoney[1][previndex] + moneyOnRoad[index];
}

int main(void)
{
	cin >> numMoney;
	for (int i = 0; i < numMoney; ++i) {
		cin >> moneyOnRoad[i];
	}
	maxMoney[0][0] = 0;
	maxMoney[1][0] = moneyOnRoad[0];
	maxMoney[2][0] = 0;
	maxMoney[0][1] = moneyOnRoad[0];
	maxMoney[1][1] = moneyOnRoad[1];
	maxMoney[2][1] = maxMoney[1][0] + moneyOnRoad[1];
	for (int i = 2; i < numMoney; ++i) {
		setMaxMoney(i);
	}
	int lastindex = numMoney - 1;
	cout << max3int(maxMoney[0][lastindex], maxMoney[1][lastindex], maxMoney[2][lastindex]) << endl;

	return 0;
}