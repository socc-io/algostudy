/* Hu-Shing algorithm implementation
author: junodeveloper (wnsgh224@naver.com)
date  : 2020.1.30.
https://github.com/junodeveloper/Hu-Shing
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
namespace HuShing {
	using ll=long long;
	using pii=pair<int,int>;
	const int maxn=200010;
	/* About Polygon */
	int n;
	ll w[maxn];
	ll CP[maxn];
	/* About H-arcs */
	struct HArc {
		int id; // calc in new_arc
		int u,v; // "
		int low; // "
		ll base; // "
		ll mul; // "
		ll num,den; // calc in dfs
		inline bool contains(HArc& b)const{
			return u<=b.u&&b.v<=v;
		}
		inline ll get_support()const{
			assert(den!=0);
			return num/den;
		}
		bool operator<(const HArc& b)const{
			return get_support()<b.get_support();
		}
		bool operator<=(const HArc& b)const{
			return get_support()<=b.get_support();
		}
		bool operator==(const HArc& b)const{
			return get_support()==b.get_support();
		}
	} h[maxn];

	int n_arcs;
	int sub[maxn]; // calc in dfs
	vector<int> child[maxn]; // calc in build_tree
	int n_pqs,qid[maxn]; // calc in dfs
	priority_queue<HArc> pq[maxn];
	vector<HArc> con[maxn];

	void new_arc(int u,int v) {
		assert(u<=v);
		++n_arcs;
		h[n_arcs].id=n_arcs;
		h[n_arcs].u=u;
		h[n_arcs].v=v;
		h[n_arcs].low=w[u]<w[v]?u:v;
		h[n_arcs].mul=(ll)w[u]*w[v];
		h[n_arcs].base=CP[v]-CP[u]-h[n_arcs].mul;
	}
	void build_tree(vector<pii>& lst) {
		vector<int> stk;
		new_arc(1,n+1); // h[1] is root
		for(auto& it:lst) {
			new_arc(it.first,it.second);
			while(!stk.empty()&&
				h[n_arcs].contains(h[stk.back()])) {
				child[n_arcs].push_back(stk.back());
				stk.pop_back();
			}
			stk.push_back(n_arcs);
		}
		while(!stk.empty()) {
			child[1].push_back(stk.back());
			stk.pop_back();
		}
	}

	void one_sweep() {
		vector<int> stk;
		vector<pii> tmp,lst;
		for(int i=1;i<=n;i++) {
			while(stk.size()>=2 && w[stk.back()]>w[i]) {
				tmp.push_back({stk[stk.size()-2],i});
				stk.pop_back();
			}
			stk.push_back(i);
		}
		while(stk.size()>=4) {
			int Vt_1=stk[stk.size()-2];
			tmp.push_back({1,Vt_1});
			stk.pop_back();
		}
		for(auto& it:tmp) {
			if(it.first==1||it.second==1) continue;
			lst.push_back(it);
		}
		build_tree(lst);
	}
	void prepare() {
		int V1=min_element(w+1,w+n+1)-w;
		rotate(w+1,w+V1,w+n+1);
		w[n+1]=w[1];
		for(int i=1;i<=n+1;i++) {
			CP[i]=(ll)w[i]*w[i-1];
			CP[i]+=CP[i-1];
		}
	}
	ll get_mn_mul(int node) {
		if(node==1) return (ll)w[1]*w[2]+(ll)w[1]*w[n];
		HArc& cur=h[node];
		if(cur.u==cur.low) {
			if(con[cur.u].empty()||!cur.contains(con[cur.u].back())) {
				return (ll)w[cur.u]*w[cur.u+1];
			} else return con[cur.u].back().mul;
		} else {
			if(con[cur.v].empty()||!cur.contains(con[cur.v].back())) {
				return (ll)w[cur.v]*w[cur.v-1];
			} else return con[cur.v].back().mul;
		}
		assert(0); // never happens
		return 0;
	}
	inline void add_arc(int cur_node,HArc& arc) {
		pq[qid[cur_node]].push(arc);
		con[arc.u].push_back(arc);
		con[arc.v].push_back(arc);
	}
	inline void remove_arc(int cur_node) {
		const HArc& hm=pq[qid[cur_node]].top();
		con[hm.u].pop_back();
		con[hm.v].pop_back();
		pq[qid[cur_node]].pop();
	}
	void merge_pq(int node) {
		int max_child=-1;
		for(auto& it:child[node])
			if(max_child==-1||sub[max_child]<sub[it])
				max_child=it;
		qid[node]=qid[max_child];
		auto& cur_pq=pq[qid[node]];
		for(auto& it:child[node]) {
			if(it==max_child) continue;
			auto& child_pq=pq[qid[it]];
			while(!child_pq.empty()) {
				cur_pq.push(child_pq.top());
				child_pq.pop();
			}
		}
	}
	void dfs(int node) {
		HArc& cur=h[node];
		sub[node]=1;
		if(child[node].empty()) {
			qid[node]=++n_pqs;
			cur.den=cur.base;
			cur.num=(ll)w[cur.low]*(cur.den+cur.mul-get_mn_mul(node));
			add_arc(node,cur);
			return;
		}
		cur.den=cur.base;
		for(auto& it:child[node]) {
			dfs(it);
			sub[node]+=sub[it];
			cur.den-=h[it].base;
		}
		cur.num=(ll)w[cur.low]*(cur.den+cur.mul-get_mn_mul(node));
		merge_pq(node);
		auto& cur_pq=pq[qid[node]];
		while(!cur_pq.empty()&&cur_pq.top().get_support()>=w[cur.low]) {
			auto hm=cur_pq.top();
			cur.den+=hm.den;
			remove_arc(node); // this must be done before calculating cur.num!
			cur.num=(ll)w[cur.low]*(cur.den+cur.mul-get_mn_mul(node));
		}
		while(!cur_pq.empty()&&cur<=cur_pq.top()) {
			auto hm=cur_pq.top();
			cur.den+=hm.den;
			remove_arc(node);
			cur.num+=hm.num;
		}
		add_arc(node,cur);
	}
	ll getans() {
		dfs(1);
		ll ans=0;
		auto& cur_pq=pq[qid[1]];
		while(!cur_pq.empty()) {
			ans+=cur_pq.top().num;
			cur_pq.pop();
		}
		return ans;
	}
	void init() {
		int i;
		memset(w,0,sizeof(w));
		memset(CP,0,sizeof(CP));
		memset(sub,0,sizeof(sub));
		memset(qid,0,sizeof(qid));
		for(i=0;i<=n_pqs;i++) while(!pq[i].empty()) pq[i].pop();
		for(i=0;i<=n;i++) { 
			while(!con[i].empty()) con[i].pop_back();
			while(!child[i].empty()) child[i].pop_back();
		}
		n_arcs=0;
	}
	void input(const vector<ll>& arr) {
		n=arr.size();
		for(int i=1;i<=n;i++) w[i]=arr[i-1];
	}
	ll solve(const vector<ll>& arr) {
		if(arr.size()<2) return 0;
		if(arr.size()==2) return arr[0]*arr[1];
		init();
		input(arr);
		prepare();
		one_sweep();
		return getans();
	}
}

int main() {
	int n; scanf("%d", &n);
  vector<ll> v(n+1);
  for (int i = 0; i < n; i++) {
    int a, b; scanf("%d%d", &a, &b);
    if (i == 0) v[0] = a;
    v[i+1] = b;
  }
	printf("%lld\n",HuShing::solve(v));
	return 0;
}
