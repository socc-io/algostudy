#include<iostream>
using namespace std;

#define INF 0x7FFFFFFF

typedef long long ll;

int n;
int arr[100001];
int tree[262160];

int make_tree(int node, int left, int right)
{
    if(left == right) tree[node] = left;
    else {
        int mid = (left+right)/2;
        int m1 = make_tree(node*2, left, mid);
        int m2 = make_tree(node*2+1, mid+1, right);
        tree[node] = arr[m1] < arr[m2] ? m1 : m2;
    }
    return tree[node];
}
int get_min(int node, int start, int end, int left, int right)
{
    if(left > end || right < start) return -1;
    if(start <= left && right <= end) return tree[node];
    int mid = (left+right)/2;
    int m1 = get_min(node*2, start, end, left, mid);
    int m2 = get_min(node*2+1, start, end, mid+1, right);
    if(m1 == -1) return m2;
    if(m2 == -1) return m1;
    return arr[m1] < arr[m2] ? m1 : m2;
}

ll get_max_area(int start, int end)
{
    int m = get_min(1, start, end, 0, n-1);
    ll area = (ll)(end-start+1)*arr[m];
    if(start <= m-1) {
        ll tmp = get_max_area(start, m-1);
        if(tmp > area) area = tmp;
    }
    if(end >= m+1) {
        ll tmp = get_max_area(m+1, end);
        if(tmp > area) area = tmp;
    }
    return area;
}

int main()
{
    while(1) {
        scanf("%d", &n);
        if(n == 0) break;
        for(int i=0; i<n; ++i) scanf("%d", arr+i);
        make_tree(1, 0, n-1);
        printf("%lld\n", get_max_area(0, n-1)); 
    }
}
