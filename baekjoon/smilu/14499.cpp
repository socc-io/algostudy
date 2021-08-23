#include <bits/stdc++.h>
using namespace std;

struct Dice {
    int state[6];
    int x, y;
    Dice(int x, int y): x(x), y(y) {
        memset(state, 0, sizeof(state));
    }
    void Transition(const int dd[]) {
        int nextstate[6];
        for (int i = 0; i < 6; i++) nextstate[i] = state[dd[i]];
        for (int i = 0; i < 6; i++) state[i] = nextstate[i];
    }
    void RollUp() {
        x -= 1;
        const int dd[] = {4, 0, 2, 3, 5, 1};
        Transition(dd);
    }
    void RollDown() {
        x += 1;
        const int dd[] = {1, 5, 2, 3, 0, 4};
        Transition(dd);
    }
    void RollLeft() {
        y -= 1;
        const int dd[] = {3, 1, 0, 5, 4, 2};
        Transition(dd);
    }
    void RollRight() {
        y += 1;
        const int dd[] = {2, 1, 5, 0, 4, 3};
        Transition(dd);
    }
    void Interact(vector< vector<int> > & board) {
        int & b = board[x][y];
        if (b == 0) b = state[5];
        else { state[5] = b; b = 0; }
    }
    int Top() { return state[0]; }
};

int main() {
    int n, m, x, y, k;
    cin >> n >> m >> x >> y >> k;

    vector< vector<int> > board(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> board[i][j];
        }
    }

    Dice dice(x, y);

    while (k--) {
        int c; cin >> c;
        switch (c) {
        case 1:
            if (dice.y < m-1)
                dice.RollRight();
            else continue;
            break;
        case 2:
            if (dice.y > 0)
                dice.RollLeft();
            else continue;
            break;
        case 3:
            if (dice.x > 0)
                dice.RollUp();
            else continue;
            break;
        case 4:
            if (dice.x < n-1)
                dice.RollDown();
            else continue;
            break;
        }
        dice.Interact(board);
        cout << dice.Top() << '\n';
    }
    return 0;
}
