#include <algorithm>
#include <vector>

using namespace std;
template<typename type>
type determinant(type vector<vector<type>> matrix)
{
	int result = 0;
	vector<vector<type>> temp;
	vector<type> column(matrix.size() - 1);
	for (int i = 0; i < matrix.size() - 1; i++)
		temp.push_back(column);
	if(matrix.size()==1)
		return matrix[0][0];
	for (int p = 0; p < matrix.size(); p++)
	{
		int h = 0, k = 0;
		for (int i = 0; i < matrix.size(); i++)
		{
			for (int j = 0; j < matrix.size(); j++)
			{
				if (j==p)
					continue;
				temp[h][k] = a[i][j];
				k++;
				if(k == matrix.size() - 1)
				{
					h++;
					k=0;
				}
			}
		}
		det += matrix[0][p] * pow(-1,p) * determinant<type>(temp);	
	}
	return det;
}