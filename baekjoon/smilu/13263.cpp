#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long lld;

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

int n;
lld a[100000];
lld b[100000];
lld dp[100000];
LinearMinCHT<lld> cht;

int main(void)
{
  scanf("%d", &n);
  for (int i = 0; i < n; i++) scanf("%lld", &a[i]);
  for (int i = 0; i < n; i++) scanf("%lld", &b[i]);
  cht.insert(b[0], 0);
  for (int i = 1; i < n; i++) {
    dp[i] = cht.query(a[i]);
    cht.insert(b[i], dp[i]);
  }
  printf("%lld\n", dp[n-1]);
}
