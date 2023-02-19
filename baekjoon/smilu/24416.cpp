#include <bits/stdc++.h>
using namespace std;

int fibo[100];

int main() {
    fibo[0] = 1;
    fibo[1] = 1;
    for (int i = 2; i < 100; i++) {
        fibo[i] = fibo[i-1] + fibo[i-2];
    }

    int n; scanf("%d", &n);
    printf("%d %d", fibo[n-1], n-2);
}
