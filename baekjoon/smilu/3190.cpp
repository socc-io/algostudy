#include <bits/stdc++.h>
using namespace std;

const int dd[4][2] = {
    {0, 1}, {1, 0}, {0, -1}, {-1, 0}
};

struct Game {
    int n;
    queue< pair<int, int> > snake;
    vector< vector<bool> > apple;
    vector< vector<bool> > route;

    int dir;
    Game(int n):
        n(n),
        apple(n, vector<bool>(n, false)),
        route(n, vector<bool>(n, false)),
        dir(0) {
        
        snake.push(make_pair(0, 0));
        route[0][0] = true;
    }
    ~Game() {}

    void rotate_right() { dir = (dir + 1) % 4; }
    void rotate_left()  { dir = (dir + 3) % 4; }

    bool move_forward() {
        auto head = snake.back();
        auto next = make_pair(head.first + dd[dir][0], head.second + dd[dir][1]);

        if (next.first < 0 || next.first >= n) return false;
        if (next.second < 0 || next.second >= n) return false;
        
        if (route[next.first][next.second]) return false;

        snake.push(next);
        route[next.first][next.second] = true;

        if (apple[next.first][next.second]) {
            apple[next.first][next.second] = false;
        } else{
            auto tail = snake.front();
            route[tail.first][tail.second] = false;
            snake.pop();
        }

        return true;
    }
};

int main() {
    int n; cin >> n;

    Game game(n);

    int an; cin >> an;
    for (int i = 0; i < an; i++) {
        int x, y; cin >> x >> y;
        game.apple[x - 1][y - 1] = true;
    }

    int q; cin >> q;
    queue< pair<int, char> > cmd;
    while (q--) {
        int t; char ch;
        cin >> t >> ch;
        cmd.push(make_pair(t, ch));
    }

    for (int t = 0;; t++) {
        if (cmd.front().first == t) {
            if (cmd.front().second == 'L') game.rotate_left();
            else game.rotate_right();
            cmd.pop();
        }
        
        if (false == game.move_forward()) {
            cout << t + 1 << '\n';
            break;
        }

        // std::printf("x: %d, y: %d\n", game.snake.back().first, game.snake.back().second);
    }
}
