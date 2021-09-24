#include <bits/stdc++.h>
using namespace std;

#define EMPTY (0)

const int dd[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};

struct Plate {
    int m, count;
    vector<int> values;
    int offset;
    Plate(int m): m(m), count(m), values(m), offset(0) {}
    void Read(istream & stream) {
        for (int i = 0; i < m; i++) {
            stream >> values[i];
        }
    }
    void Rotate(int v) {
        while (v < 0) v += m;
        offset = (offset + v) % m;
    }
    int& At(int i) {
        return values[(offset + i) % m];
    }
    void Remove(int y) {
        At(y) = 0;
        --count;
    }
    int Sum() const {
        int sum = 0;
        for (int v: values) sum += v;
        return sum;
    }
    void EqualizeOne(int mean, int base) {
        for (int &v: values) {
            if (v == 0) continue;
            const int vc = v * base;
            if (vc > mean) --v;
            else if (vc < mean) ++v;
        }
    }
};

struct PlateStack {
    int n, m;
    vector<Plate> plates;
    PlateStack(int n, int m): n(n), m(m), plates(n, Plate(m)) {}
    int Sum() const {
        int sum = 0;
        for (const Plate &p: plates) sum += p.Sum();
        return sum;
    }
    void ReadPlates(istream & stream) {
        for (int i = 0; i < n; i++) {
            plates[i].Read(stream);
        }
    }
    void RotateX(int x, int d, int k) {
        const int n_rot = d ? k : -k;
        for (int i = x-1; i < n; i += x) {
            plates[i].Rotate(n_rot);
        }
    }
    void RemoveNeighbors() {
        int count = 0;
        vector<vector<bool>> visit(n, vector<bool>(m, false));
        for (int x = 0; x < n; x++) {
            for (int y = 0; y < m; y++) {
                if (plates[x].At(y) == 0) continue;
                auto neighbors = FindNeighbors(x, y, visit);
                if (neighbors.size() <= 1) continue;
                count += neighbors.size();
                for (auto p: neighbors) {
                    plates[p.first].Remove(p.second);
                }
            }
        }
        if (count == 0) {
            Equalize();
        }
    }
    void Equalize() {
        const int sum = Sum();
        int base = 0;
        for (auto& p: plates) base += p.count;
        // printf("[Equalize] sum: %d, base: %d\n", sum, base);
        for (auto& p: plates) p.EqualizeOne(sum, base);
    }
    vector<pair<int, int>> FindNeighbors(int x, int y, vector<vector<bool>> & visit) {
        vector<pair<int, int>> result;
        int target = plates[x].At(y);
        FindNeighbors(x, y, target, result, visit);
        return result;
    }
    void FindNeighbors(int x, int y, int target, vector<pair<int, int>> & dest, vector<vector<bool>> & visit) {
        int& v = plates[x].At(y);
        if (v != target) return;
        if (visit[x][y]) return;
        visit[x][y] = true;
        dest.push_back(make_pair(x, y));
        for (int di = 0; di < 4; di++) {
            int nx = x + dd[di][0], ny = y + dd[di][1];
            if (nx < 0 || nx >= n) continue;
            while (ny < 0) ny += m;
            ny %= m;
            FindNeighbors(nx, ny, target, dest, visit);
        }
    }
    void Print() {
        for (int x = 0; x < n; x++) {
            for (int y = 0; y < m; y++) {
                printf("%d ", plates[x].At(y));
            }
            puts("");
        } puts("");
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m, t;
    cin >> n >> m >> t;

    PlateStack stack(n, m);
    stack.ReadPlates(cin);

    while (t--) {
        int x, d, k;
        cin >> x >> d >> k;
        stack.RotateX(x, d, k);
        stack.RemoveNeighbors();
        // stack.Print();
    }

    cout << stack.Sum();
}
