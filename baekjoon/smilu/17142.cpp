#include <bits/stdc++.h>
using namespace std;

#define EMPTY 0
#define WALL 1
#define VIRUS 2

const int dd[4][2] = {
    {0, 1}, {0, -1}, {1, 0}, {-1, 0},
};

const int inf = 0x3f3f3f3f;

int ReplaceInf(int x, int rep) {
    return x == inf ? rep : x;
}

struct Laboratory {
    int n;
    int tiles[50][50];

    Laboratory(int n, istream & stream): n(n) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                stream >> tiles[i][j];
            }
        }
    }

    vector< vector<int> > GetDistancesFromPoint(int x, int y) const {
        vector< vector<int> > distances(n, vector<int>(n, inf));
        queue< pair<int, int> > q;
        q.push(make_pair(x, y));
        distances[x][y] = 0;
        while (!q.empty()) {
            int x = q.front().first;
            int y = q.front().second;
            q.pop();
            for (int i = 0; i < 4; i++) {
                int nx = x + dd[i][0];
                int ny = y + dd[i][1];
                if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
                if (tiles[nx][ny] == WALL) continue;
                if (distances[nx][ny] != inf) continue;
                distances[nx][ny] = distances[x][y] + 1;
                q.push(make_pair(nx, ny));
            }
        }
        return distances;
    }

    vector<int> MapDistancesOfEmptyTiles(const vector< vector<int> > & distances) const {
        vector<int> result;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (tiles[i][j] != EMPTY) continue;
                result.push_back(distances[i][j]);
            }
        }
        return result;
    }

    vector< vector<int> > GetDistancesFromViruses() const {
        vector< vector<int> > result;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (tiles[i][j] != VIRUS) continue;
                result.push_back(
                    MapDistancesOfEmptyTiles(
                        GetDistancesFromPoint(i, j)
                    )
                );
            }
        }
        return result;
    }
};

/**
 * @example [false, true, true, false, false] => [1, 2]
 */
vector<int> MapBoolToIndices(const vector<bool> & b) {
    vector<int> result;
    for (int i = 0; i < b.size(); i++) {
        if (b[i]) result.push_back(i);
    }
    return result;
}

/**
 * @example [[1,4,7], [2,5,8], [3,6,9]], [1, 2] => [2, 5, 8]
 */
vector<int> Min(const vector< vector<int> > & arr, const vector<int> & indices) {
    int m = arr[0].size();
    vector<int> result(m);
    for (int i = 0; i < m; i++) {
        int min_v = arr[indices[0]][i];
        for (int j = 1; j < indices.size(); j++) {
            min_v = min(min_v, arr[indices[j]][i]);
        }
        result[i] = min_v;
    }
    return result;
}

int Max(const vector<int> & arr) {
    return *max_element(arr.begin(), arr.end());
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    const Laboratory lab(n, cin);

    // distances from viruses to empty tiles [virusIndex][emptyTileIndex] ( not spatial )
    const vector< vector<int> > distances = lab.GetDistancesFromViruses();

    assert(distances.size() > 0); // At least one virus exists in laboratory
    if (distances[0].size() == 0) { // There is no empty tile
        cout << "0\n";
        return 0;
    }

    int answer = inf;

    vector<bool> selected(distances.size(), false);
    for (int i = 0; i < m; i++) selected[distances.size() - (i+1)] = true;
    do {
        answer = min(answer, Max(Min(distances, MapBoolToIndices(selected))));
    } while (next_permutation(selected.begin(), selected.end()));

    cout << ReplaceInf(answer, -1) << '\n';

    return 0;
}
