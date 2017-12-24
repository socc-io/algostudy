#include<cstdio>

int V[10000],L[10000],R[10000];
void re(int p)
{
	if(L[p]  != 0) re(L[p]);
	if(R[p] != 0) re(R[p]);
	printf("%d\n", V[p]);
}
int main()
{
	for(int i=0; ~scanf("%d",V+i); ++i) for(int c = 0; c != i;
		c = V[i] < V[c] ?
			(L[c] == 0 ? (L[c] = i) : L[c]) :
			(R[c] == 0 ? (R[c] = i) : R[c]));
	re(0);
}
