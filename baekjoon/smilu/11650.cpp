#include <stdio.h>
#include <stdlib.h>

struct Point {
    int x, y;

    bool operator < (const Point other) const {
        if (x == other.x) return y < other.y;
        return x < other.x;
    }
};

int ComparePoint(const void * a, const void * b) {
    if (*(Point*)a < *(Point*)b) return -1;
    if (*(Point*)b < *(Point*)a) return 1;
    return 0;
}

void sort(Point * arr, int len) {
    qsort(arr, len, sizeof(Point), ComparePoint);
}

Point points[100000];

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &points[i].x, &points[i].y);
    }

    sort(points, n);

    for (int i = 0; i < n; i++) {
        printf("%d %d\n", points[i].x, points[i].y);
    }

    return 0;
}
