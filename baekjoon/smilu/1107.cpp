#include<iostream>
using namespace std;

int n, k, tmp;
bool but[10];

int check(int val)
{
    if(val == 0) {
        if(but[0]) return -1;
        return n+1;
    }
    int q = val;
    int cnt=0;
    while(q) {
        if(but[q%10]) {
            return -1;
        }
        q /= 10;
        ++cnt;
    }
    return abs(n-val)+cnt;
 }

int main()
{
    scanf("%d%d", &n, &k);
    for(int i=0; i<k; ++i) {
        scanf("%d", &tmp);
        but[tmp] = true;
    }
    int q = 0xFFFFF;
    for(int i=0; i<=1000000; ++i) {
        if((tmp = check(i)) == -1) continue;
        if(tmp < q) q = tmp;
    }
    int w = abs(100-n);
    printf("%d", q<w?q:w);
}
