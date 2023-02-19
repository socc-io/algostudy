#include <bits/stdc++.h>

class SubsetAlphaCounter: private std::vector<int> {
public:
    typedef std::unique_ptr<SubsetAlphaCounter> Ptr;

    SubsetAlphaCounter(const std::string_view &s, char t): std::vector<int>(s.length() + 1) {
        at(0) = 0;
        for (int i = 1; i < size(); i++) {
            at(i) = at(i-1) + (s[i-1] == t);
        }
    }

    int query(int l, int r) {
        return at(r) - at(l);
    }
};

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    std::string s;
    std::cin >> s;

    std::vector<SubsetAlphaCounter::Ptr> counters(26);
    for (char ch = 'a'; ch <= 'z'; ch++) {
        counters[ch - 'a'] = std::make_unique<SubsetAlphaCounter>(s, ch);
    }

    int t;
    std::cin >> t;
    while (t--) {
        char alpha;
        int l, r;
        std::cin >> alpha >> l >> r;
        std::cout << counters[alpha - 'a']->query(l, r+1) << '\n';
    }

    return 0;
}
