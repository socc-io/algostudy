#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool test(string s) {
    int a_count = 0;
    for (char ch: s) a_count += (ch == 'a');

    while(s.length() > 1) {
        while (s.length() > 1 && s[0] == 'a') {
            s = s.substr(1);
            --a_count;
        }

        while (s.length() > 1 && s[s.length()-1] == 'a') {
            s = s.substr(0, s.length() - 1);
            --a_count;
        }
        
        if (a_count <= 0) return false;

        int b_count = 0;
        while ((2*b_count) < s.length()-1 && s[b_count] == 'b' && s[s.length()-1-b_count] == 'b') ++b_count;
        if (b_count % a_count != 0) return false;

        s = s.substr(b_count, s.length() - 2*b_count);
    }

    return s[0] == 'a';
}

vector<bool> solution(vector<string> a) {
    vector<bool> answer;
    for (string &s: a)
        answer.push_back(test(s));
    return answer;
}

int main() {
    cout << test("aabb") << '\n';
    return 0;
}