#include<iostream>
using namespace std;

int w[1<<21];
int s[1<<20];
int n;
int sw;

void balance(int pos)
{
	if(pos >= (1 << n)) return;
	int l = pos<<1, r = (pos<<1)+1;
	balance(l); balance(r);
	int ls = s[l] + w[l], rs = s[r] + w[r];
	int Ms = ls > rs ? ls : rs;
	int ms = ls < rs ? ls : rs;
	s[pos] = Ms;
	sw += Ms - ms;
}

int main()
{
	scanf("%d", &n);
	int wc = (((1<<n)-1)<<1) + 2;
	for(int i=2; i<wc; ++i) scanf("%d", w+i), sw += w[i];
	balance(1);
	printf("%d", sw);
}