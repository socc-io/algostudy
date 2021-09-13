#include <bits/stdc++.h>
using namespace std;

const int inf = 0x3f3f3f3f;

void AssignRect(vector< vector<int> > & mat, int x1, int x2, int y1, int y2, int v) {
    for (int i = x1; i < x2; i++) {
        for (int j = y1; j < y2; j++) {
            mat[i][j] = v;
        }
    }
}

int GetMinMaxDiff(const vector<int> & arr) {
    const int max_value = *max_element(arr.begin(), arr.end());
    const int min_value = *min_element(arr.begin(), arr.end());
    return max_value - min_value;
}

vector< vector<int> > GetSplit(int n, int x, int y, int d1, int d2) {
    vector< vector<int> > result(n, vector<int>(n, 0));

    AssignRect(result, 0, x+d1, 0, y+1, 0);
    AssignRect(result, 0, x+d2+1, y+1, n, 1);
    AssignRect(result, x+d1, n, 0, y-d1+d2, 2);
    AssignRect(result, x+d2+1, n, y-d1+d2, n, 3);

    for (int i = x; i <= x+d1+d2; i++) {
        const int begin_j = y-i+x + (max(0, i-x-d1) << 1);
        const int end_j   = y+i-x - (max(0, i-x-d2) << 1) + 1;
        for (int j = begin_j; j < end_j; j++) {
            result[i][j] = 4;
        }
    }

    return result;
}

struct City {
    int n;
    vector< vector<int> > populations;

    City(int n): n(n), populations(n, vector<int>(n)) {}
    void ReadPopulations(istream & stream) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                stream >> populations[i][j];
            }
        }
    }

    vector<int> GetSumPopulations(const vector< vector<int> > & split) const {
        vector<int> result(5, 0);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                result[split[i][j]] += populations[i][j];
            }
        }
        return result;
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    City city(n);
    city.ReadPopulations(cin);

    int answer = inf;

    for (int x = 0; x < n; x++)
    for (int y = 0; y < n; y++)
    for (int d1 = 1; d1 <= y; d1++)
    for (int d2 = 1; x+d1+d2 < n && y+d2 < n; d2++) {
        const auto split = GetSplit(n, x, y, d1, d2);
        const auto pops = city.GetSumPopulations(split);
        answer = min(answer, GetMinMaxDiff(pops));
    }

    cout << answer;

    return 0;
}
