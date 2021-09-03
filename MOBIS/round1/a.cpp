#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool including(vector<int> & arr, int target) {
    auto it = lower_bound(arr.begin(), arr.end(), target);
    if (it == arr.end()) return false;
    return *it == target;
}

vector<int> splitInt(int target) {
    vector<int> result;
    
    if (target == 0) {
        result.push_back(0);
        return result;
    }

    while (target) {
        result.push_back(target % 10);
        target /= 10;
    }

    return result;
}

bool dfs(vector<bool> & visit, vector<vector<int>> & dice, vector<int> & digits, int index) {
    if (index >= digits.size()) return true;

    for (int i = 0; i < dice.size(); i++) {
        if (visit[i]) continue;
        if (including(dice[i], digits[index])) {
            visit[i] = true;
            if (dfs(visit, dice, digits, index + 1))
                return true;
            visit[i] = false;
        }
    }
    return false;
}

bool test(vector<vector<int>> & dice, int target) {
    vector<int> digits = splitInt(target);

    if (digits.size() > dice.size()) return false;

    vector<bool> visit(dice.size(), false);
    return dfs(visit, dice, digits, 0);
}

int solution(vector<vector<int>> dice) {
    for (auto &row: dice) {
        sort(row.begin(), row.end());
    }

    for (int i = 1; i <= 10000; i++) {
        if (false == test(dice, i)) {
            return i;
        }
    }

    return 10000;
}