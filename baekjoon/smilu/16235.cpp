#include <bits/stdc++.h>
using namespace std;

struct Tree {
    int age;
    Tree(int age = 0): age(age) {}
    bool operator<(const Tree & other) const {
        return age < other.age;
    }
};

struct Tile {
    int soil;
    int deadsoil;
    vector<Tree> trees;

    Tile():
        soil(5),
        deadsoil(0)
        {}
    
    void AddNewTrees(int n) {
        while (n--) trees.emplace_back(1);
    }

    int size() const { return trees.size(); }

    void FeedTrees() {
        sort(trees.begin(), trees.end());
        int survived = 0;
        for (int i = 0; i < trees.size(); i++) {
            if (soil < trees[i].age) {
                deadsoil += trees[i].age >> 1;
            } else {
                soil -= trees[i].age;
                trees[i].age++;
                survived++;
            }
        }
        trees.resize(survived);
    }

    void TurnDeadIntoSoil() {
        soil += deadsoil;
        deadsoil = 0;
    }

    int GetNumOfBreedableTrees() const {
        int num = 0;
        for (const Tree & t: trees) {
            num += (t.age % 5) == 0;
        }
        return num;
    }
};

struct Robot {
    int n;
    vector< vector<int> > A;
    Robot(int n):
        n(n),
        A(n, vector<int>(n))
        {}
    void ReadA(istream & stream) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                stream >> A[i][j];
            }
        }
    }
    void FeedTiles(vector< vector<Tile> > & tiles) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                tiles[i][j].soil += A[i][j];
            }
        }
    }
};

struct Land {
    int n;
    vector< vector<Tile> > tiles;
    Robot s2d2;

    Land(int n):
        n(n),
        tiles(n, vector<Tile>(n)),
        s2d2(n)
        {}
    
    int size() const {
        int result = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                result += tiles[i][j].size();
            }
        }
        return result;
    }
    
    void ReadTrees(int m, istream & stream) {
        while(m--) {
            int x, y, z;
            cin >> x >> y >> z;
            tiles[x-1][y-1].trees.emplace_back(z);
        }
    }

    void Breed(int x, int y, int num) {
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (i == 0 && j == 0) continue;
                int nx = x + i, ny = y + j;
                if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
                tiles[nx][ny].AddNewTrees(num);
            }
        }
    }

    void PassSpring() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                tiles[i][j].FeedTrees();
            }
        }
    }

    void PassSummer() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                tiles[i][j].TurnDeadIntoSoil();
            }
        }
    }

    void PassAutumn() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int numChild = tiles[i][j].GetNumOfBreedableTrees();
                Breed(i, j, numChild);
            }
        }
    }

    void PassWinter() {
        s2d2.FeedTiles(tiles);
    }

    void PassAYear() {
        PassSpring();
        PassSummer();
        PassAutumn();
        PassWinter();
    }
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    int n, m, k;
    cin >> n >> m >> k;

    Land land(n);
    land.s2d2.ReadA(cin);
    land.ReadTrees(m, cin);

    while (k--) land.PassAYear();

    cout << land.size() << '\n';

    return 0;
}
