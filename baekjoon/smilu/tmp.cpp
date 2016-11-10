#include <iostream>
#include <map>

using namespace std;


int main(int argc, char** argv)
{
	map<int, int> m;
	m[0] = 3;
	m.find(0)->second = 4;
	cout << m[0] << endl;

	return 0;
}