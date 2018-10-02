//
// BIT.h
//
// binary indexed tree
//
// INPUT: tree
//
// OUTPUT: query
//
// Time: O(log(2N))
//	
//
#include <algorithm>
#include <vector>

using namespace std;
template<typename Te, typename Tv>
class bit {
private:
	vector<Tv> raw;
	size_t size;

public:
	bit(const vector<Tv>& vector)
	{
		this->size = vector.size() + 1;
		this->raw.assign(this->size, 0);
		for (int i = 0; i < vector.size(); i++)
			this->update(i, vector[i]);
	}
	void update(Te index, const Tv& value)
	{
		index++;
		while (index <= this->size)
		{
			this->raw[index] += value;
			index += index & (-index);
		}
	}
	Tv sum(Te index)
	{
		index++;
		int result = 0;
		while (index)
		{
			result += this->raw[index];
			index -= index & (-index);
		}
		return result;
	}
	~bit() {}
};
/*
#include <iostream>
int main()
{
	vector<int> v = { 2, 1, 1, 3, 2, 3, 4, 5, 6, 7, 8, 9 };
	bit<int, int> tree(v);
	cout << tree.sum(5) << endl;
	tree.update(3, 6);
	cout << tree.sum(5) << endl;

}
*/