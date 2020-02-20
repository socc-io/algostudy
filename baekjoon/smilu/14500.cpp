#include <cstdio>
#include <vector>
using namespace std;

// IOZSTLJ
int samples[][4][2] = {
  { // I
    {0, 0},
    {1, 0},
    {2, 0},
    {3, 0},
  },
  { // O
    {0, 0},
    {1, 0},
    {0, 1},
    {1, 1},
  },
  { // Z
    {0, -1},
    {0, 0},
    {1, 0},
    {1, 1},
  },
  { // S
    {0, 1},
    {0, 0},
    {1, 0},
    {1, -1},
  },
  { // T
    {0, 0},
    {1, 0},
    {0, 1},
    {0, -1},
  },
  { // L
    {0, 0},
    {1, 0},
    {2, 0},
    {2, 1},
  },
  { // J
    {0, 0},
    {1, 0},
    {2, 0},
    {2, -1},
  },
};

struct filter {
  pair<int, int> p[4];
};

pair<int, int> rotate(pair<int, int> p) {
  return make_pair(-p.second, p.first);
}
void rotate_filter(filter* from, filter* to) {
  for (int i = 0; i < 4; i++) {
    to->p[i] = rotate(from->p[i]);
  }
}
void apply_sample(filter* f, int index) {
  for (int i = 0; i < 4; i++) {
    f->p[i] = make_pair(samples[index][i][0], samples[index][i][1]);
  }
}

filter filters[19];
int n, m;
int tile[500][500];

int apply_filter(filter* f) {
  int max = 0;
  for (int x = -3; x < n + 3; x++) {
    for (int y = -3; y < m + 3; y++) {
      int sum = 0;
      bool out = false;
      for (int i = 0; i < 4; i++) {
        int nx = x + f->p[i].first;
        int ny = y + f->p[i].second;
        if (nx < 0 || nx >= n || ny < 0 || ny >= m) {
          out = true;
          break;
        }
        sum += tile[nx][ny];
      }
      if (out) continue;
      if (sum > max) max = sum;
    }
  }
  return max;
}

int apply_filters() {
  int max = 0;
  for (int i = 0; i < 19; i++) {
    int val = apply_filter(filters + i);
    if (val > max) max = val;
  }
  return max;
}

int main(void)
{
  // IOZSTLJ
  for (int i = 0; i < 7; i++) {
    apply_sample(filters + i, i);
  }
  rotate_filter(filters, filters + 7);
  rotate_filter(filters + 2, filters + 8);
  rotate_filter(filters + 3, filters + 9);
  rotate_filter(filters + 4, filters + 10);
  rotate_filter(filters + 10, filters + 11);
  rotate_filter(filters + 11, filters + 12);
  rotate_filter(filters + 5, filters + 13);
  rotate_filter(filters + 13, filters + 14);
  rotate_filter(filters + 14, filters + 15);
  rotate_filter(filters + 6, filters + 16);
  rotate_filter(filters + 16, filters + 17);
  rotate_filter(filters + 17, filters + 18);

  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      scanf("%d", &tile[i][j]);
    }
  }

  printf("%d", apply_filters());
}