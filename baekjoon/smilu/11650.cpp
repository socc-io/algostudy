#include <stdio.h>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

struct Point {
    int x, y;

    bool operator < (const Point other) const {
        if (x == other.x) return y < other.y;
        return x < other.x;
    }
};

int my_hash(const char* s, int len) {
    int result = 0;
    for (int i = 0; i < len; i++) {
        result += (s[i] - 35);
        result *= 299;
    }
    return result;
}

int my_int_hash(int x) {
    return x * 255;
}

int main() {
    int n;
    scanf("%d", &n);

    vector<Point> points(n);

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &points[i].x, &points[i].y);
    }

    sort(points.begin(), points.end());

    for (int i = 0; i < n; i++) {
        printf("%d %d\n", points[i].x, points[i].y);
    }

    return 0;
}
