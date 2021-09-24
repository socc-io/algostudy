#include <bits/stdc++.h>
using namespace std;

bool isdigit(char ch) {
    return '0' <= ch && ch <= '9';
}

int n;
vector<int> digits;
vector<char> ops;

vector< vector<int> > candidates;

int solve(int r1, char op, int r2) {
    if (op == '*') return r1*r2;
    if (op == '+') return r1+r2;
    if (op == '-') return r1-r2;
    return 0;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    n = (n+1)>>1;

    digits.reserve(n);
    ops.reserve(n-1);
    candidates.resize(n);
    
    string line; cin >> line;
    for (int i = 0, j = 0; i < n-1; i++) {
        digits.push_back(line[j++] - '0');
        ops.push_back(line[j++]);
    }
    digits.push_back(line[(n<<1)-2] - '0');

    if (n == 1) {
        cout << digits[0];
        return 0;
    }

    candidates[0].push_back(digits[0]);
    candidates[1].push_back(solve(digits[0], ops[0], digits[1]));
    for (int i = 2; i < n; i++) {
        candidates[i].reserve(candidates[i-1].size() + candidates[i-2].size());
        for (int prev: candidates[i-1]) {
            candidates[i].push_back(solve(prev, ops[i-1], digits[i]));
        }
        int next = solve(digits[i-1], ops[i-1], digits[i]);
        for (int prev: candidates[i-2]) {
            candidates[i].push_back(solve(prev, ops[i-2], next));
        }
        sort(candidates[i].begin(), candidates[i].end()); 
        candidates[i].erase(unique(candidates[i].begin(), candidates[i].end()), candidates[i].end());
    }

    // for (int i = 0; i < n; i++) {
    //     std::printf("candidates[%d]: ", i);
    //     for (int c: candidates[i]) {
    //         std::printf("%d ", c);
    //     }
    //     std::puts("");
    // }

    cout << *max_element(candidates[n-1].begin(), candidates[n-1].end());
}

