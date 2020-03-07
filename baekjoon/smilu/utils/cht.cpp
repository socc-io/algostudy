#include <vector>
using namespace std;

template<typename T>
class LinearMinCHT{
	public:
		vector< pair<T, T> > stk;
		long long idx;
	
		double cross(long long a, long long b){
			double t1 = (double)(stk[b].second - stk[a].second);
			double t2 = (double)(stk[a].first - stk[b].first);
			return t1/t2;
		}
		
		void insert(T a, T b){
			stk.emplace_back(a, b);
			while(stk.size() > 2 &&
			cross(stk.size()-3, stk.size()-2) > cross(stk.size()-2, stk.size()-1)){
				stk[stk.size()-2] = stk.back();
				stk.pop_back();
			}
		}
		
		T query(T x){
			while(idx+1 < stk.size() && cross(idx, idx+1) <= x){
				idx++;
			}
			return x*stk[idx].first + stk[idx].second;
		}
		
		LinearMinCHT(){
			idx = 0; stk.clear();
		}
};