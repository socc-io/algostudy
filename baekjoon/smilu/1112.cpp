#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    vector<char> buf;

    int x, b; cin >> x >> b;

    bool was_minus = x < 0;
    x = abs(x);

    while (x) {
        buf.push_back('0' + (x % b));
        x /= b;
    }

    reverse(buf.begin(), buf.end());
    if (was_minus) cout << '-';
    for (int i = 0; i < buf.size(); i++) {
        cout << buf[i];
    }
}
