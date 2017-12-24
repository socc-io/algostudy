
#include <iostream>
#include <algorithm>

using namespace std;

#define INF 1234567890

int n, m;
int arr[100000];
pair<int,int> tree[300000];

int read_int()
{
	int ret = 0;
	char ch;
	while((ch = getchar()) >= '0' && ch <= '9') {
		ret = ret*10 + ch - '0';
	}
	return ret;
}

void build_tree(int node, int start, int end)
{
	if(start == end) {
		tree[node] = make_pair(arr[start], arr[start]);
	} else {
		int mid = (start + end) / 2;
		build_tree(node*2, start, mid);
		build_tree(node*2+1, mid+1, end);
		tree[node] = make_pair(
			min(tree[node*2].first, tree[node*2+1].first),
			max(tree[node*2].second, tree[node*2+1].second)
		);
	}
}

pair<int,int> find_tree(int node, int start, int end, int left, int right)
{
	if(right < start || end < left) return make_pair(INF, -1);
	if(left <= start && end <= right) return tree[node];

	int mid = (start + end) / 2;

	pair<int,int> l = find_tree(node*2, start, mid, left, right);
	pair<int,int> r = find_tree(node*2+1, mid+1, end, left, right);

	int m = min(l.first, r.first);
	int M = max(l.second, r.second);

	return make_pair(m, M);
}

int main(void)
{
	n = read_int();
	m = read_int();
	for(int i=0; i<n; ++i) {
		arr[i] = read_int();
	}
	build_tree(1, 0, n-1);
	for(int i=0; i<m; ++i) {
		int start, end;
		start = read_int();
		end = read_int();
		--start, --end;
		pair<int,int> res = find_tree(1, 0, n-1, start, end);
		printf("%d %d\n", res.first, res.second);
	}
}