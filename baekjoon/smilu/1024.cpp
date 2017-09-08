#include<iostream>
using namespace std;

int main()
{
    int n, l;
    scanf("%d%d", &n, &l);
    int n2 = n<<1;
    for(int k=l; k<=100; ++k) {
        if(n2%k != 0) continue;
        int q = n2/k + 1 - k;
        if(q < 0 || (q&1)) continue;
        int s = q>>1;
        for(int i=s; i<s+k; ++i) {
            printf("%d ", i);
        }
        return 0;
    }
    puts("-1");
}
