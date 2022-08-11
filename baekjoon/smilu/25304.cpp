#include <bits/stdc++.h>
using namespace std;

int main() {
    int ans_total;
    int n_type;
    cin >> ans_total >> n_type;

    int total = 0;
    
    for (int i = 0; i < n_type; i++) {
        int cost, num_items;
        cin >> cost >> num_items;

        total += cost * num_items;
    }

    bool is_same = ans_total == total;

    cout << (is_same ? "Yes" : "No");

    return 0;
}
