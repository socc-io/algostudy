#include <iostream>
#include <vector>

using namespace std;

class Building
{
public :
	vector<Building*> next;
	vector<Building*> prev;
	int cost;
	int costsum;
public :
	Building() {
		costsum = -1;
	}
	int getCostSum() {
		if(costsum != -1) return costsum;
		int max = 0;
		for(vector<Building*>::iterator it = prev.begin(); it != prev.end(); ++it) {
			int newval = (*it)->getCostSum();
			if(max < newval) {
				max = newval;
			}
		}
		costsum = max + cost;
		return costsum;
	}
};

int main(int argc, char** argv)
{
	int T;
	int build_num, build_rule_num, obj;
	vector<Building*> all_build;
	cin >> T;
	for(int test_idx=0; test_idx<T; ++test_idx)
	{
		cin >> build_num >> build_rule_num;
		for(int i=0;i<build_num;++i) {
			int cost;
			cin >> cost;
			Building *build = new Building();
			build->cost = cost;
			all_build.push_back(build);
		}
		for(int i=0;i<build_rule_num;++i) {
			int from, to;
			cin >> from >> to;
			--from; --to;
			Building* fromBuilding = all_build[from];
			Building* toBuilding = all_build[to];
			fromBuilding->next.push_back(toBuilding);
			toBuilding->prev.push_back(fromBuilding);
		}
		cin >> obj;
		obj--;
		Building* objBuilding = all_build[obj];
		int result_cost = objBuilding->getCostSum();
		printf("%d\n", result_cost);

		for(int i=0;i<build_num;++i) {
			delete all_build[i];
		}
		all_build.clear();
	}

	return 0;
}