#include <stdio.h>
#include <vector>
#include <iostream>		 
using namespace std;
vector<int> vList;
int n;
bool isFind = false;
void recursiveSolver(int iterator = 0)
{
	if (!isFind)
	{
		if (iterator == n)
		{
			for (vector<int>::iterator it = vList.begin(); it != vList.end(); ++it)
			{
				printf("%d", *it);
			}
			printf("\n");
			isFind = true;
			vList.pop_back();
		}
		else
		{
			int next_iterator = iterator + 1;
			for (int i = 1; i <= 3; ++i)
			{
				vList.push_back(i);
				int ListSize = vList.size();
				int groupNum = ListSize / 2;
				bool isOK = true;
				for (int j = 1; j <= groupNum; ++j)
				{
					vector<int>::iterator leftFirst = vList.end() - j - j;
					vector<int>::iterator rightFirst = vList.end() - j;
					bool check = true;
					for (int k = 0; k < j; ++k)
					{
						if (*leftFirst != *rightFirst) check = false;
						++leftFirst;
						++rightFirst;
					}
					if (check)
					{
						vList.pop_back();
						isOK = false;
						break;
					}
				}
				if (isOK)
				{
					recursiveSolver(next_iterator);
				}
			}
			vList.pop_back();
		}
	}
}
int main(void)
{
	scanf_s("%d", &n);
	recursiveSolver();
}
