/*
 * author: smilu97
 * description:
 *   algorithm solving: https://www.welcomekakao.com/learn/courses/30/lessons/42890
 */

#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

int test_comb(int comb, vector<vector<string>>& relation) {
    unordered_set<string> s;
    int num_col = relation[0].size();
    for(auto row: relation) {
        string q;
        for (int i = 0; i < num_col; i++) {
            if (comb & (1 << i)) q += row[i] + ',';
        }
        if (s.find(q) != s.end()) return 0;
        s.insert(q);
    }
    return 1;
}

int solution(vector<vector<string>> relation) {
    vector<int> candidates;
    int answer = 0;
    int num_col = relation[0].size();
    int max_bit = 1 << num_col;
    for (int i = 1; i < max_bit; i++) {
        if (test_comb(i, relation)) candidates.push_back(i);
    }
    for (int a: candidates) {
        int sc = 1;
        for (int b: candidates) {
            if (a == b) continue;
            if (a | b == b) {
                sc = 0;
                break;
            }
        }
        answer += sc;
    }
    return answer;
}