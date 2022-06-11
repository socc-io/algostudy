#include <bits/stdc++.h>
using namespace std;

int pow10[10];

int ext_digit(int x, int p) {
    return (x / pow10[p]) % 10;
}

int case1(int l, int u, int p, int x) {

}

int sub(int l, int u, int p, int x) {
    const int lp = ext_digit(l, p), up = ext_digit(u, p);
    if (x < lp) {
        return (((u / pow10[p+1]) - (l / pow10[p+1])) * pow10[p]);
    } else if (x == lp) {
        return ((u % pow10[p]) - (l % pow10[p]) + 1) +
          (((u / pow10[p+1]) - (l / pow10[p+1])) * pow10[p]);
    } else if (x < up) {
        return (((u / pow10[p+1]) - (l / pow10[p+1]) + 1) * pow10[p]);
    } else if (x == up) {
        return ((u % pow10[p]) - (l % pow10[p]) + 1) +
          (((u / pow10[p+1]) - (l / pow10[p+1])) * pow10[p]);
    } else {
        return (((u / pow10[p+1]) - (l / pow10[p+1])) * pow10[p]);
    }
}

int main() {
    int l, u;
    scanf("%d %d", &l, &u);
    
    pow10[0] = 1;
    for (int i = 1; i < 10; i++) pow10[i] = pow10[i-1] * 10;

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            ans += sub(l, u, i, j) * j;
        }
    }

    printf("%d", ans);
}
