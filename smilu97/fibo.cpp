#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Matrix22
{
public :
	int dat[2][2];
	Matrix22 operator*(Matrix22 val)
	{
		Matrix22 ret;
		ret.dat[0][0] = dat[0][0] * val.dat[0][0] + dat[0][1] * val.dat[1][0];
		ret.dat[0][1] = dat[0][0] * val.dat[0][1] + dat[0][1] * val.dat[1][1];
		ret.dat[1][0] = dat[0][0] * val.dat[1][0] + dat[1][1] * val.dat[1][0];
		ret.dat[1][1] = dat[1][0] * val.dat[0][1] + dat[1][1] * val.dat[1][1];
		return ret;
	}
}

vector<Matrix22> fiboMatrix;

int main(void)
{

}