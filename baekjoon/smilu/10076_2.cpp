#include <bits/stdc++.h>
using namespace std;
 
#define MAXN 100005
#define MAXT 300005
typedef long long lld;
 
static int N, S, T, K;
static int A[MAXN], P[MAXN];
static lld D[MAXT], E[MAXT];
 
struct Z{
    int a, x;
} B[MAXN];
 
struct NODE{
    int cnt; lld sum;
    NODE *left, *right;
} container[262144], *root;
 
NODE *new_node()
{
    NODE *ret = &container[K++];
    ret->cnt = ret->sum = 0;
    ret->left = ret->right = 0;
    return ret;
}
 
void write(NODE *now, int s, int e, int n, int v)
{
    if (n < s || e < n) return;
    if (s == e){
        if (v >= 0){
            now->cnt = 1;
            now->sum = v;
        }else{
            now->cnt = now->sum = 0;
        }
        return;
    }
    if (!now->left) now->left = new_node(), now->right = new_node();
    int m = (s+e)>>1;
    write(now->left, s, m, n, v);
    write(now->right, m+1, e, n, v);
    now->cnt = now->left->cnt + now->right->cnt;
    now->sum = now->left->sum + now->right->sum;
}
 
lld get_highest(NODE *now, int s, int e, int &left)
{
    if (left <= 0) return 0;
    if (now->cnt <= left){
        left -= now->cnt;
        return now->sum;
    }
    if (s == e) return 0;
    int m = (s+e)>>1;
    lld ret = get_highest(now->left, s, m, left);
    if (left > 0) ret += get_highest(now->right, m+1, e, left);
    return ret;
}
 
void calc(int l, int r, int s, int e)
{
    if (s > e) return;
    int m = (s+e)>>1, t;
    D[m] = -1;
    for (int i=l;i<=r;i++){
        write(root, 1, N, P[i], A[i]);
        int left = m-(i-S);
        if (left <= 0) break;
        lld sum = get_highest(root, 1, N, left);
        if (D[m] < sum)
            D[m] = sum, t = i;
    }
    if (s == e) return;
    for (int i=l;i<=r;i++) write(root, 1, N, P[i], -1);
    calc(l, t, s, m-1);
    for (int i=l;i<t;i++) write(root, 1, N, P[i], A[i]);
    calc(t, r, m+1, e);
}
 
void calc2(int l, int r, int s, int e)
{
    if (s > e) return;
    int m = (s+e)>>1, t;
    E[m] = -1;
    for (int i=r;i>=l;i--){
        write(root, 1, N, P[i], A[i]);
        int left = m-(S-i)*2;
        if (left <= 0) break;
        lld sum = get_highest(root, 1, N, left);
        if (E[m] < sum)
            E[m] = sum, t = i;
    }
    if (s == e) return;
    for (int i=l;i<=r;i++) write(root, 1, N, P[i], -1);
    calc2(t, r, s, m-1);
    for (int i=t+1;i<=r;i++) write(root, 1, N, P[i], A[i]);
    calc2(l, t, m+1, e);
}
 
lld proc()
{
    for (int i=1;i<=N;i++) B[i].a = A[i], B[i].x = i;
    sort(B+1, B+N+1, [](const Z &a, const Z &b){
        return a.a > b.a;
    });
    for (int i=1;i<=N;i++) P[B[i].x] = i;
    K = 0; root = new_node();
    calc(S, N, 1, T);
    K = 0; root = new_node();
    if (S > 1) calc2(1, S-1, 3, T);
    else for (int i=0;i<=T;i++) E[i] = 0;
    lld ret = D[T];
    for (int i=1;i<=T;i++) ret = max(ret, E[i] + D[T-i]);
    return ret;
}
 
lld findMaxAttraction(int n, int start, int d, int arr[])
{
    N = n, S = start+1, T = d;
    for (int i=1;i<=N;i++) A[i] = arr[i-1];
    lld ret = proc();
    if (!start) return ret;
    reverse(A+1, A+N+1); S = N-S+1;
    return max(ret, proc());
}

int arr[100000];
int main(void)
{
  int n, start, d;
  scanf("%d%d%d", &n, &start, &d);
  for (int i = 0; i < n; i++) scanf("%d", arr+i);
  printf("%lld\n", findMaxAttraction(n, start, d, arr));
}
