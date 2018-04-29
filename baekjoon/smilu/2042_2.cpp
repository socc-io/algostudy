
#include <cstdio>
#include <cstdlib>

#define ARR_SZ (1000001)
#define TREE_SZ (ARR_SZ * 2 + 1)

// #define DEBUG

typedef long long lld;

int n, m, k, tree_sz;

lld arr[ARR_SZ];
lld tree[TREE_SZ];

void build_tree();
lld _build_tree(int tree_idx, int left, int right);

void modify_tree(int idx, lld val);
void _modify_tree(int tree_idx, int arr_idx, int left, int right, lld diff);

void print_subsum(int from, int to);
lld _get_subsum(int tree_idx, int left, int right, int from, int to);

int main(void)
{
	scanf("%d%d%d", &n, &m, &k);
	m += k;
	for(int i=1; i<=n; ++i) scanf("%lld", arr + i);
	build_tree();
	for(int i=0; i<m; ++i) {
		lld op, arg1, arg2;
		scanf("%lld%lld%lld", &op, &arg1, &arg2);
		if (op == 1) {
			modify_tree(arg1, arg2);
			arr[arg1] = arg2;
		} else {  // if (op == 2)  // print
			print_subsum(arg1, arg2);
		}
	}
}

void build_tree() {
#ifdef DEBUG
	printf("build_tree()\n");
#endif
	_build_tree(1, 1, n);
}

lld _build_tree(int tree_idx, int left, int right)
{
#ifdef DEBUG
	printf("    _build_tree(%d,%d,%d)\n", tree_idx, left, right);
#endif
	int mid = ((left + right) >> 1);
	return (tree[tree_idx] = left == right ?
		arr[left] : 
			_build_tree(tree_idx*2, left, mid) +
			_build_tree(tree_idx*2+1, mid+1, right));
}

void modify_tree(int idx, lld val)
{
#ifdef DEBUG
	printf("modify_tree(%d,%d)\n", idx, val);
#endif
	_modify_tree(1, idx, 1, n, val - arr[idx]);
}

void _modify_tree(int tree_idx, int arr_idx, int left, int right, lld diff)
{
#ifdef DEBUG
	printf("    _modify_tree(%d,%d,%d,%d,%d)\n", tree_idx, arr_idx, left, right, diff);
#endif
	if (arr_idx < left || arr_idx > right) return;  // arr_idx is out of [left, right]
	tree[tree_idx] += diff;

	if(left == right) return;

	int mid = ((left + right) >> 1);
	_modify_tree(tree_idx*2,   arr_idx, left,  mid,   diff);
	_modify_tree(tree_idx*2+1, arr_idx, mid+1, right, diff);
}

void print_subsum(int from, int to)
{
#ifdef DEBUG
	printf("print_subsum(%d,%d): ", from, to);
#endif
	printf("%lld\n", _get_subsum(1, 1, n, from, to));
}
lld _get_subsum(int tree_idx, int left, int right, int from, int to)
{
	if(from  <= left && right <= to)   return tree[tree_idx];
	if(right <  from || to    <  left) return 0;

	int mid = ((left + right) >> 1);
	return 
		_get_subsum(tree_idx*2,   left,  mid,   from, to) +
		_get_subsum(tree_idx*2+1, mid+1, right, from, to);
}