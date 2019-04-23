/*
 * author: smilu97
 * description:
 *   algorithm solving of https://www.acmicpc.net/problem/1036
 */

#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

#define NSZ 70

int N, K;

inline int convi(char c)
{
    return c <= 57 ? c - 48 : c - 55;
}
inline char convc(int v)
{
    return v >= 10 ? v + 55 : v + 48;
}

class numb
{
public:
    char s[NSZ];
    void input()
    {
        scanf("%s", s);
        int len = strlen(s);
        int mid = (len - 1) >> 1;
        for (int i = 0, l = len - 1; i <= mid; i++, l--) {
            char tmp = convi(s[i]);
            s[i] = convi(s[l]);
            s[l] = tmp;
        }
    }
    int getlen() const {
        int r = NSZ - 1;
        while (!s[r] && r >= 0) r--; r++;
        return r > 0 ? r : 1;
    }
    void print()
    {
        int len = getlen();
        for (int i = len - 1; i >= 0; i--)
            printf("%c", convc(s[i]));
    }
    void add(numb &b) {
        int carry = 0;
        for (int i = 0; i < NSZ; i++) {
            int tmp = s[i] + b.s[i] + carry;
            carry = tmp >= 36;
            s[i] = tmp % 36;
        }
    }
    bool operator<(const numb& b) const {
        for (int i = NSZ - 1; i >= 0; i--)
            if (s[i] != b.s[i]) return s[i] < b.s[i];
        return false;
    }
};

numb sum;
numb n[50];
numb p[36];
vector<int> comp;

int main(void)
{
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        n[i].input();
        sum.add(n[i]);
    }
    scanf("%d", &K);
    for (int i = 0; i < N; i++) {
        int len = n[i].getlen();
        for (int j = 0; j < 36; j++) {
            numb tmp;
            for (int k = 0; k < NSZ; k++)
                tmp.s[k] = k < len && n[i].s[k] == j
                    ? 35 - j : 0;
            p[j].add(tmp);
        }
    }
    comp.reserve(36);
    for (int i = 0; i < 36; i++)
        comp.push_back(i);
    sort(comp.begin(), comp.end(), [](int a, int b) {
        return p[b] < p[a];
    });
    for (int i = 0; i < K; i++)
        sum.add(p[comp[i]]);
    sum.print();
}