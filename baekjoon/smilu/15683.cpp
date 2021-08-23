#include <bits/stdc++.h>

using namespace std;

const int dd[4][2] = {
    {0, 1}, {-1, 0}, {0, -1}, {1, 0},
};

const int camtype_desc[][4][4] = {
    {{ 0,  0,  0,  0}, { 0,  0,  0,  0}, { 0,  0,  0,  0}, { 0,  0,  0,  0}},
    {{ 0,  0,  0,  0}, { 1,  0,  0,  0}, { 2,  0,  0,  0}, { 3,  0,  0,  0}},
    {{ 0,  2,  0,  0}, { 1,  3,  0,  0}, { 0,  0,  0,  0}, { 0,  0,  0,  0}},
    {{ 0,  1,  0,  0}, { 1,  2,  0,  0}, { 2,  3,  0,  0}, { 0,  3,  0,  0}},
    {{ 0,  1,  2,  0}, { 1,  2,  3,  0}, { 2,  3 , 0,  0}, { 3,  0,  1,  0}},
    {{ 0,  1,  2,  3}, { 0,  0,  0,  0}, { 0,  0,  0,  0}, { 0,  0,  0,  0}},
};

const int num_dir_camtype[] = {0, 1, 2, 2, 3, 4};
const int num_case_camtype[] = {0, 4, 2, 4, 4, 1};

enum Direction {
    RIGHT = 0,
    UP,
    LEFT,
    DOWN,
};

#define WALL (6)

struct Point {
    int x, y;
    Point() {}
    Point(int x, int y): x(x), y(y) {}

    Point Forward(int dir) const {
        return Point(x + dd[dir][0], y + dd[dir][1]);
    }
};

struct PointMultiSet {
    int n, m;
    vector< vector<int> > count;
    int count_nz;

    PointMultiSet(int n, int m):
        n(n), m(m), count(n, vector<int>(m, 0)), count_nz(0) {}
    
    void Apply(Point p, int d) {
        int & v = count[p.x][p.y];
        if (v == 0) ++count_nz;
        v += d;
        if (v == 0) --count_nz;
    }
    
    void Apply(const vector<Point> &points, int d) {
        for (const Point &p: points)
            Apply(p, d);
    }
};

struct Room {
    int n, m;
    vector< vector<int> > tile;

    Room(int n, int m):
        n(n), m(m), tile(n, vector<int>(m)) {}
    
    void ReadInput() {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                cin >> tile[i][j];
    }
    
    bool OutOfBound(Point p) const {
        return
            p.x < 0 || p.x >= n ||
            p.y < 0 || p.y >= m;
    }

    int At(Point p) const { return tile[p.x][p.y]; }

    const int GetNumWall() const {
        int result = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                result += tile[i][j] == 6;
            }
        }
        return result;
    }

    vector<Point> GetCamPoints() const {
        vector<Point> result;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                const int t = tile[i][j];
                if (t != 0 && t != 6) {
                    result.push_back(Point(i, j));
                }
            }
        }

        return result;
    }

    vector<Point> GetRayTrajectory(Point from, int dir) const {
        vector<Point> result;

        Point it = from;
        while (!OutOfBound(it) && At(it) != WALL) {
            result.push_back(it);
            it = it.Forward(dir);
        }

        return result;
    }

    vector<Point> GetCameraCoverageSingleCase(Point origin, int type, int case_idx) const {
        vector<Point> result;
        result.push_back(origin);

        const int * directions = camtype_desc[type][case_idx];

        for (int d = 0; d < num_dir_camtype[type]; d++) {
            int dir = directions[d];
            Point from = Point(origin.x + dd[dir][0], origin.y + dd[dir][1]);
            auto ray = GetRayTrajectory(from, dir);
            copy(ray.begin(), ray.end(), back_inserter(result));
        }

        return result;
    }

    vector< vector<Point> > GetCameraCoverages(Point origin, int type) const {
        vector< vector<Point> > result;
        
        for (int i = 0; i < num_case_camtype[type]; i++) {
            auto coverage = GetCameraCoverageSingleCase(origin, type, i);
            result.push_back(coverage);
        }

        return result;
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    Room room(n, m);

    room.ReadInput();

    const auto campoints = room.GetCamPoints();

    vector< vector< vector<Point> > > coverages;
    for (Point campoint: campoints) {
        auto coverage = room.GetCameraCoverages(campoint, room.At(campoint));
        coverages.push_back(coverage);
    }

    const int num_cam = campoints.size();
    const int num_wall = room.GetNumWall();
    int max_coverage = 0;

    PointMultiSet set(n, m);

    function<void(int)> dfs = [&](int index) -> void {
        if (index >= num_cam) {
            max_coverage = max(max_coverage, set.count_nz);
            return;
        }

        for (const auto & cov: coverages[index]) {
            set.Apply(cov, 1);
            dfs(index + 1);
            set.Apply(cov, -1);
        }
    };

    dfs(0);

    cout << n*m - num_wall - max_coverage << '\n';

    return 0;
}


