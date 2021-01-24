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

typedef long long ll;
typedef pair<ll, ll> p;

#define INF 0x7fffffffffffffff

struct CHT{ // max cht
	ll a[101010], b[101010], c[101010];
	int pv, top;

	void clear(){
		pv = top = 0;
	}

	ll f(ll idx, ll x){
		return a[idx]*x + b[idx];
	}

	void insert(ll aa, ll bb, ll cc){
		if(top >= 1 && aa == a[top-1]){
			c[top-1] = cc; return;
		}
		while(top >= 2 && (b[top-1] - b[top-2]) * (a[top-2] - aa) >= (bb - b[top-2]) * (a[top-2] - a[top-1])) top--;
		a[top] = aa;
		b[top] = bb;
		c[top] = cc;
		top++;
		if(pv >= top) pv = top - 1;
	}

	p query(ll x){
		while(pv+1 < top && a[pv+1]*x + b[pv+1] > a[pv]*x + b[pv]) pv++;
		return {f(pv, x), c[pv]};
	}
};