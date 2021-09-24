#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int and_all(vector<int> & a) {
    int result = 0xffffffff;
    for (int v: a) result &= v;
    return result;
}

int rightside(int v, int from) {
    return (v & ((1 << from) - 1)) + 1;
}

int solve(vector<int> & a) {
    int result = 0;
    for (int i = 30; i >= 0; i--) {
        int aa = and_all(a);
        if (aa == 0) return result;
        if ((aa & (1 << i)) == 0) continue;
    
        int min_right = rightside(a[0], i);
        int max_index = 0;
        for (int j = 1; j < a.size(); j++) {
            int count = rightside(a[j], i);
            if (count < min_right) {
                min_right = count;
                max_index = j;
            }
        }

        a[max_index] -= min_right;
        result += min_right;
    }
    return result;
}

vector<int> subvector(const vector<int> & arr, int start, int len) {
    vector<int> result(len);
    for (int i = 0; i < len; i++) {
        result[i] = arr[start + i];
    }
    return result;
}

vector<int> solution(vector<int> m, vector<int> b) {
    vector<int> answer;
    int acc = 0;
    for (int len: m) {
        vector<int> buf = subvector(b, acc, len);
        answer.push_back(solve(buf));
        acc += len;
    }
    return answer;
}
