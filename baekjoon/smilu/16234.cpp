#include <bits/stdc++.h>
using namespace std;

const int dd[4][2] = {
    {1, 0}, {-1, 0}, {0, 1}, {0, -1},
};

int GetDiff(int a, int b) { return abs(a - b); }
bool Openable(int r1, int r2, int l, int r) {
    int diff = GetDiff(r1, r2);
    return l <= diff && diff <= r;
}

struct Environment {
    int n;
    vector< vector<int> > populations;

    Environment(int n):
        n(n),
        populations(n, vector<int>(n, 0))
        {}

    void ReadPopulations(istream & stream) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                stream >> populations[i][j];
            }
        }
    }

    vector< pair<int, int> > GetUnionOfCountry(int x, int y, int l, int r, vector< vector<bool> > & visit) const {
        vector< pair<int, int> > unions;
        queue< pair<int, int> > q;

        q.push(make_pair(x, y));
        visit[x][y] = true;

        while (!q.empty()) {
            pair<int, int> u = q.front();
            q.pop();

            unions.push_back(u);

            for (int i = 0; i < 4; i++) {
                int nx = u.first + dd[i][0];
                int ny = u.second + dd[i][1];

                if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
                if (visit[nx][ny]) continue;
                if (!Openable(populations[u.first][u.second], populations[nx][ny], l, r)) continue;

                visit[nx][ny] = true;
                q.push(make_pair(nx, ny));
            }
        }
        return unions;
    }

    bool FlattenUnions(const vector< pair<int, int> > & unions) {
        bool modified = false;

        int sum_populations = 0;
        for (auto u: unions) sum_populations += populations[u.first][u.second];
        int mean_populations = sum_populations / unions.size();

        for (auto u: unions) {
            modified |= populations[u.first][u.second] != mean_populations;
            populations[u.first][u.second] = mean_populations;
        }

        return modified;
    }

    bool OpenDoors(int l, int r) {
        bool modified = false;

        vector< vector<bool> > visit(n, vector<bool>(n, false));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (visit[i][j]) continue;
                vector< pair<int, int> > unions = GetUnionOfCountry(i, j, l, r, visit);
                modified |= FlattenUnions(unions);
                for (auto u: unions) visit[u.first][u.second] = true;
            }
        }
        
        return modified;
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, l, r;
    cin >> n >> l >> r;

    Environment env(n);
    env.ReadPopulations(cin);

    int answer = 0;
    while (env.OpenDoors(l, r)) answer++;
    cout << answer << '\n';

    return 0;
}
