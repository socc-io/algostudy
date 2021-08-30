#include <bits/stdc++.h>
using namespace std;

enum Color {
    WHITE = 0,
    YELLOW,
    RED,
    ORANGE,
    GREEN,
    BLUE,
};

typedef tuple<Color, Color, Color> ColorTuple;

ColorTuple ReverseColorTuple(ColorTuple t) {
    return make_tuple(get<2>(t), get<1>(t), get<0>(t));
}

#define UP 0
#define FRONT 1
#define LEFT 2
#define RIGHT 3
#define BACKWARD 4
#define BOTTOM 5

const char * color_to_char_lst = "wyrogb";
char ColorToChar(Color color) {
    return color_to_char_lst[(int) color];
}

int CharToSide(char c) {
    if (c == 'L') return LEFT;
    if (c == 'R') return RIGHT;
    if (c == 'F') return FRONT;
    if (c == 'B') return BACKWARD;
    if (c == 'U') return UP;
    if (c == 'D') return BOTTOM;
    return -1;
}

const int rotate_33_map[9] = {
    6, 3, 0, 7, 4, 1, 8, 5, 2,
};

#define F_TOP 0
#define F_RIGHT 1
#define F_BOTTOM 2
#define F_LEFT 3

const int f_map[4][3] = {
    {0, 1, 2},
    {2, 5, 8},
    {6, 7, 8},
    {0, 3, 6},
};

const int rotate_cube_map[6][4][3] = {
    {{FRONT, F_TOP, 1}, {LEFT, F_TOP, 1}, {BACKWARD, F_TOP, 1}, {RIGHT, F_TOP, 1}},
    {{UP, F_BOTTOM, 1}, {RIGHT, F_LEFT, 1}, {BOTTOM, F_TOP, -1}, {LEFT, F_RIGHT, -1}},
    {{UP, F_LEFT, 1}, {FRONT, F_LEFT, 1}, {BOTTOM, F_LEFT, 1}, {BACKWARD, F_RIGHT, -1}},
    {{UP, F_RIGHT, 1}, {BACKWARD, F_LEFT, -1}, {BOTTOM, F_RIGHT, 1}, {FRONT, F_RIGHT, 1}},
    {{UP, F_TOP, 1}, {LEFT, F_LEFT, -1}, {BOTTOM, F_BOTTOM, -1}, {RIGHT, F_RIGHT, 1}},
    {{FRONT, F_BOTTOM, 1}, {RIGHT, F_BOTTOM, 1}, {BACKWARD, F_BOTTOM, 1}, {LEFT, F_BOTTOM, 1}},
};

struct Face {
    Color c[9];

    void Setup(Color ic) {
        for (int i = 0; i < 9; i++)
            c[i] = ic;
    }

    void Rotate() {
        Color t[9];
        memcpy(t, c, sizeof(c));
        for (int i = 0; i < 9; i++)
            c[i] = t[rotate_33_map[i]];
    }
    
    ColorTuple GetSide(int side, int rev = 1) const {
        ColorTuple result = make_tuple(c[f_map[side][0]], c[f_map[side][1]], c[f_map[side][2]]);
        return rev == 1 ? result : ReverseColorTuple(result);
    }

    void SetSide(int side, ColorTuple t, int rev = 1) {
        if (rev != 1) t = ReverseColorTuple(t);
        c[f_map[side][0]] = get<0>(t);
        c[f_map[side][1]] = get<1>(t);
        c[f_map[side][2]] = get<2>(t);
    }

    void PrintState() const {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                cout << ColorToChar(c[i*3 + j]);
            }
            cout << '\n';
        }
    }
};

struct Cube {
    Face f[6];

    Cube() {
        f[UP].Setup(WHITE);
        f[BOTTOM].Setup(YELLOW);
        f[FRONT].Setup(RED);
        f[BACKWARD].Setup(ORANGE);
        f[LEFT].Setup(GREEN);
        f[RIGHT].Setup(BLUE);
    }
    
    void RotateByCode(char d) {
        int side = CharToSide(d);
        f[side].Rotate();

        auto rotate_map = rotate_cube_map[side];
        ColorTuple tmp = f[rotate_map[3][0]].GetSide(rotate_map[3][1], rotate_map[3][2]);
        for (int i = 3; i > 0; i--) {
            f[rotate_map[i][0]].SetSide(rotate_map[i][1], f[rotate_map[i-1][0]].GetSide(rotate_map[i-1][1], rotate_map[i-1][2]), rotate_map[i][2]);
        }
        f[rotate_map[0][0]].SetSide(rotate_map[0][1], tmp, rotate_map[0][2]);
    }

    void RotateByCode(char d, char c) {
        int rc = c == '+' ? 1 : 3;
        while (rc--) RotateByCode(d);
    }
};

void solve() {
    string s_buf;
    Cube cube;

    int n;
    cin >> n;
    while (n--) {
        cin >> s_buf;
        cube.RotateByCode(s_buf[0], s_buf[1]);
    }

    cube.f[UP].PrintState();
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--) solve();

    return 0;
}
