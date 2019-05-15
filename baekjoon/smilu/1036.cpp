/*
 * author: smilu97
 * description:
 *   algorithm solving of https://www.acmicpc.net/problem/1036
 */

#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

#define BI_SIZE 55

inline char to_ch(char val) {
    if (val < 10) return val + '0';
    else return val + ('A' - 10);
}
inline char to_in(char ch) {
    if (ch <= '9') return ch - '0';
    else return ch - ('A' - 10);
}

struct Bigint {
    char data[BI_SIZE];
    void clear() {
        memset(data, 0, BI_SIZE);
    }
    int get_length() {
        int i = BI_SIZE - 1;
        while (data[i] == 0 && i >= 0) i--;
        return i + 1;
    }
    void parse(char* str) {
        int len = strlen(str);
        for (int i = 0; i < len; i++) {
            data[i] = to_in(str[len - 1 - i]);
        }
    }
    void add(Bigint & b) {
        char carry = 0;
        for (int i = 0; i < BI_SIZE; i++) {
            char tmp = data[i] + b.data[i] + carry;
            data[i] = tmp % 36;
            carry = tmp >= 36;
        }
    }
    void add_pos(int pos, char num) {
        char carry = num;
        for (int i = pos; i < BI_SIZE; i++) {
            char tmp = data[i] + carry;
            data[i] = tmp % 36;
            carry = tmp >= 36;
        }
    }
    void to_str(char* str) {
        bool zero = true;
        for (int i = get_length() - 1; i >= 0; i--) {
            *str++ = to_ch(data[i]);
            zero = false;
        }
        if (zero) *str++ = '0';
        *str = '\0';
    }
    void print() {
        char tmp[51];
        to_str(tmp);
        puts(tmp);
    }
    bool operator<(Bigint & b) const {
        int i = BI_SIZE - 1;
        while (data[i] == b.data[i] && i > 0) i--;
        return data[i] < b.data[i];
    }
    Bigint() { clear(); }
};

int main(void)
{
    int N, K;
    vector<Bigint> arr(50);
    vector<Bigint> pot(36);  // potential
    
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        char tmp[51];
        scanf("%s", tmp);
        arr[i].parse(tmp);
        int len = arr[i].get_length();
        for (int j = 0; j < len; j++) {
            char d = arr[i].data[j];
            pot[d].add_pos(j, 35 - d);
        }
    }
    scanf("%d", &K);

    vector<int> ind(36);
    for (int i = 0; i < 36; i++) ind[i] = i;
    sort(ind.begin(), ind.end(), [&pot](int a, int b) {
        return pot[a] < pot[b];
    });

    Bigint sum;
    for (int i = 0; i < N; i++) {
        sum.add(arr[i]);
    }
    for (int i = 0; i < K; i++) {
        sum.add(pot[ind[35 - i]]);
    }
    sum.print();

    return 0;
}
