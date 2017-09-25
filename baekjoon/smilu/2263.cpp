#include<iostream>
using namespace std;

int n, tmp;
int inorder_idx[100001];
int postorder[100000];

void f(int il, int ir, int pl, int pr)
{
    int r = postorder[pr];
    printf("%d ", r);
    int div = inorder_idx[r];
    if(div-il != 0) f(il, div-1, pl, pl+div-il-1);
    if(ir-div != 0) f(div+1, ir, pl+div-il, pr-1);
}

int main()
{
    scanf("%d", &n);
    for(int i=0; i<n; ++i) scanf("%d", &tmp),  inorder_idx[tmp] = i;
    for(int i=0; i<n; ++i) scanf("%d", postorder+i);
    f(0, n-1, 0, n-1);
}
