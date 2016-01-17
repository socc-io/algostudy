#include <stdio.h>
#include <algorithm>
#include <vector>
using namespace std;

vector<int> vStall;
int stall_num = 0;
int cow_num = 0;

void solve()
{
	vStall.sort();
	int distance = 1;
	bool fail = false;
	while(1)
	{
		int focus = 0;
		for(int i=1; i<cow_num; ++i)
		{
			int next_focus = focus;
			while(vStall[next_focus] - vStall[focus] >= distance)
			{
				++next_focus;
				if(next_focus == stall_num)
				{
					fail = true;
					break;
				}
			}
			if(fail) break;
		}
		if(fail)
		{
			printf("%d",distance);
			break;
		}
		++distance;
	}
}

int main(void)
{
	scanf("%d",&stall_num);
	scanf("%d",&cow_num);
	for(int i=0;i<stall_num; ++i)
	{
		int tmp;
		scanf("%d",&tmp);
		vStall.push_back(tmp);
	}
	solve();
}