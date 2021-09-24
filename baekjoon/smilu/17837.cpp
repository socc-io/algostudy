#include <bits/stdc++.h>

using namespace std;

#define WHITE 0
#define RED 1
#define BLUE 2

const int dd[4][2] = {
    {0, 1}, {0, -1}, {-1, 0}, {1, 0},
};

int Reverse(int d) {
    if (d < 2) return 1 - d;
    return 5 - d;
}

struct Coin {
    int direction;
    int x, y;
    Coin *up, *down;

    int GetDepth() {
        Coin *cur = this;
        int count = 0;
        while (cur) {
            cur = cur->up;
            ++count;
        }
        return count;
    }

    Coin* GetTop() {
        Coin *cur = this;
        while (cur->up) cur = cur->up;
        return cur;
    }

    Coin* GetBottom() {
        Coin *cur = this;
        while (cur->down) cur = cur->down;
        return cur;
    }

    void Reverse() {
        Coin *base = down;

        vector<Coin*> arr;
        Coin *cur = this;
        while (cur) {
            arr.push_back(cur);
            cur = cur->up;
        }
        reverse(arr.begin(), arr.end());

        base->up = arr[0];
        arr[0]->down = base;
        arr[arr.size()-1]->up = NULL;
        for (int i = 0; i < arr.size()-1; i++) {
            arr[i]->up = arr[i+1];
            arr[i+1]->down = arr[i];
        }
    }
};

struct Board {
    int n, k;
    vector< vector<int> > colors;
    Coin * coins;
    Coin * bases;

    Board(int n, int k): n(n), k(k), colors(n, vector<int>(n)) {
        coins = new Coin[k];
        bases = new Coin[n*n];
        for (int i = 0; i < n*n; i++) {
            bases[i].up = NULL;
            bases[i].down = NULL;
            bases[i].x = i/n;
            bases[i].y = i%n;
        }
    }
    ~Board() {
        delete[] coins;
        delete[] bases;
    }

    bool OutBound(int x, int y) const {
        return x < 0 || x >= n || y < 0 || y >= n;
    }

    Coin* GetBase(int x, int y) const {
        return &bases[x*n + y];
    }

    void ReadColors(istream & stream) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                stream >> colors[i][j];
            }
        }
    }

    void ReadCoins(istream & stream) {
        for (int i = 0; i < k; i++) {
            int x, y, d;
            cin >> x >> y >> d;
            --x; --y; --d;
            Coin* coin = &coins[i];
            Coin* top = GetBase(x, y)->GetTop();
            coin->down = top;
            coin->up = NULL;
            coin->direction = d;
            top->up = coin;
        }
    }

    void MoveCoin(Coin* coin, int x, int y) {
        coin->down->up = NULL;

        Coin *top = GetBase(x, y)->GetTop();
        top->up = coin;
        coin->down = top;
    }

    void StepCoin(Coin* coin, int rec = 0) {
        Coin* bottom = coin->GetBottom(); 
        int x = bottom->x, y = bottom->y;
        int nx = x + dd[coin->direction][0], ny = y + dd[coin->direction][1];
        if (OutBound(nx, ny)) {
            if (rec > 0) return;
            coin->direction = Reverse(coin->direction);
            StepCoin(coin, rec + 1);
            return;
        }

        int c = colors[nx][ny];
        if (c == WHITE) {
            MoveCoin(coin, nx, ny);
        } else if (c == RED) {
            MoveCoin(coin, nx, ny);
            coin->Reverse();
        } else if (c == BLUE) {
            if (rec <= 0) {
                coin->direction = Reverse(coin->direction);
                StepCoin(coin, rec + 1);
            }
        }
    }

    bool GetDone() const {
        for (int i = 0; i < k; i++) {
            if (coins[i].GetDepth() >= 4) return true;
        }
        return false;
    }

    bool Step() {
        if (GetDone()) return true;

        for (int i = 0; i < k; i++) {
            StepCoin(&coins[i]);
            if (GetDone()) return true;
        }

        return false;
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, k;
    cin >> n >> k;

    Board board(n, k);
    board.ReadColors(cin);
    board.ReadCoins(cin);

    int answer = 1;
    while (answer <= 1000 && !board.Step()) ++answer;
    if (answer > 1000) answer = -1;

    cout << answer;

    return 0;
}
