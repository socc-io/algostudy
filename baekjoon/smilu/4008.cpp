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
lld s[1000000];
lld dp[1000000];
lld a, b, c;
LinearMinCHT<lld> cht;

lld f(lld x) {
	return a*x*x + b*x + c;
}

inline void insert(int i)
{
	cht.insert(-2*a*s[i], dp[i] + a*s[i]*s[i] - b*s[i]);
}

int main(void)
{
  scanf("%d%lld%lld%lld", &n, &a, &b, &c);
  for (int i = 0; i < n; i++) scanf("%lld", &s[i]);
  for (int i = 1; i < n; i++) s[i] += s[i-1];

	dp[0] = f(s[0]);
	cht.insert(0, 0);
	insert(0);
	for (int i = 1; i < n; i++) {
		dp[i] = cht.query(s[i]) + f(s[i]);
		insert(i);
	}
	// for (int i = 0; i < n; i++) {
	// 	printf("%lld ", dp[i]);
	// } puts("");
	printf("%lld\n", dp[n-1]);
}
