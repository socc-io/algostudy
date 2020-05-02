#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;

struct Node {
	ll mx, mx2, cnt_mx, sum;
};

ll arr[1010101];
Node tree[4040404];

Node f(Node a, Node b){
	if (a.mx == b.mx) return {a.mx, max(a.mx2, b.mx2), a.cnt_mx + b.cnt_mx, a.sum + b.sum};
	if (a.mx > b.mx) swap(a, b);
	return {b.mx, max(a.mx, b.mx2), b.cnt_mx, a.sum + b.sum};
}

Node init(int node, int s, int e){
	if (s == e) return tree[node] = {arr[s], -1, 1, arr[s]};
	int m = s + e >> 1;
	return tree[node] = f(init(node*2, s, m), init(node*2+1, m+1, e));
}

void push(int node, int s, int e){
	if (s == e) return;
	for (auto i : {node*2, node*2+1}) {
		if (tree[node].mx < tree[i].mx) {
			tree[i].sum -= tree[i].cnt_mx * (tree[i].mx - tree[node].mx);
			tree[i].mx = tree[node].mx;
		}
	}
}

void update(int node, int s, int e, int l, int r, ll v){
	push(node, s, e);
	if (r < s || e < l || tree[node].mx <= v) return;
	if (l <= s && e <= r && tree[node].mx2 < v) {
		tree[node].sum -= tree[node].cnt_mx * (tree[node].mx - v);
		tree[node].mx = v;
		push(node, s, e);
		return;
	}
	int m = s + e >> 1;
	update(node*2, s, m, l, r, v);
	update(node*2+1, m+1, e, l, r, v);
	tree[node] = f(tree[node*2], tree[node*2+1]);
}

ll query_max(int node, int s, int e, int l, int r){
	push(node, s, e);
	if(r < s || e < l) return 0;
	if(l <= s && e <= r) return tree[node].mx;
	int m = s + e >> 1;
	return max(query_max(node*2, s, m, l, r), query_max(node*2+1, m+1, e, l, r));
}

ll query_sum(int node, int s, int e, int l, int r){
	push(node, s, e);
	if(r < s || e < l) return 0;
	if(l <= s && e <= r) return tree[node].sum;
	int m = s + e >> 1;
	return query_sum(node*2, s, m, l, r) + query_sum(node*2+1, m+1, e, l, r);
}

int main() {
	int n; scanf("%d", &n);
	for(int i=1; i<=n; i++) scanf("%d", &arr[i]);
	init(1 ,1, n);
	int q; scanf("%d", &q);
	while (q--){
		int op; scanf("%d", &op);
		ll a, b, c;
		if (op == 1){
      scanf("%lld%lld%lld", &a, &b, &c);
			update(1, 1, n, a, b, c);
		} else if (op == 2){
      scanf("%lld%lld", &a, &b);
      printf("%lld\n", query_max(1,1,n,a,b));
		} else{
			scanf("%lld%lld", &a, &b);
      printf("%lld\n", query_sum(1,1,n,a,b));
		}
	}
}