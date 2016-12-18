#include <cstdio>
#include <cstdlib>
#include <vector>
#include <map>
using namespace std;

int gcd(int a, int b)
{
	int tmp;
	if(a < b) {
		tmp = a;
		a = b;
		b = tmp;
	}
	while(b != 0) {
		tmp = a % b;
		a = b;
		b = tmp;
	}
	return a;
}

int main(void)
{
	int money;
	int item_num, pack_num;
	scanf("%d%d%d",&money,&item_num,&pack_num);
	vector< pair<int, int> > items(item_num);
	vector< pair<int, int> > packs(pack_num, {0, 0});
	vector< pair<int, int> > p;
	p.reserve(pack_num);
	for(int i=0;i<item_num;++i) {
		int now_cost, next_cost;
		scanf("%d%d",&now_cost,&next_cost);
		items[i] = {now_cost, next_cost-now_cost};
	}
	for(int i=0;i<pack_num;++i) {
		int size;
		scanf("%d",&size);
		for(int j=0;j<size;++j) {
			int item_idx, num;
			scanf("%d%d",&item_idx,&num);
			--item_idx;
			packs[i].first  += items[item_idx].first  * num;
			packs[i].second += items[item_idx].second * num;
		}
	}
	for(int i=0;i<pack_num;++i) {
		if(packs[i].second > 0 && packs[i].first <= money) {
			p.push_back(packs[i]);
		}
	}
	int p_size = p.size();
	map<int, int> profits;
	profits[0] = 0;
	vector< pair<int, int> > buffer;
	buffer.reserve(p_size);
	int max_profit = 0;
	for(int i=0;i<p_size;++i) {
		pair<int, int> now_p = p[i];
		for(auto it = profits.begin(); it != profits.end(); ++it) {
			int new_cost   = it->first  + now_p.first;
			if(new_cost > money) continue;
			int new_profit = it->second + now_p.second;
			if(max_profit < new_profit) {
				max_profit = new_profit;
			}
			buffer.push_back({new_cost, new_profit});
		}
		for(auto it = buffer.begin(); it != buffer.end(); ++it) {
			bool success = true;
			for(auto it2 = profits.begin(); it2 != profits.end(); ++it2) {
				if(it2->first <= it->first && it2->second > it->second) {
					success = false;
					break;
				}
			}
			if(!success) continue;
			for(auto it2 = profits.begin(); it2 != profits.end(); ++it2) {
				if(it2->first > it->first && it2->second <= it->second) {
					it2 = profits.erase(it2);
				}
			}
			profits[it->first] = it->second;
		}
		buffer.clear();
	}
	printf("%d", max_profit);
}