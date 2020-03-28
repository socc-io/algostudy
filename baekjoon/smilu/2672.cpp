#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

template <class T>
struct Rect {
  T x, y, h, w;
  Rect<T>() {}
  Rect<T>(T x, T y, T h, T w): x(x), y(y), h(h), w(w) {}
  Rect<T> operator*(const Rect<T> &b) const {
    T nx = max(x, b.x), ny = max(y, b.y);
    T nh = max(min(x+h, b.x+b.h) - nx, 0);
    T nw = max(min(y+w, b.y+b.w) - ny, 0);
    return Rect<T>(nx, ny, nh, nw);
  }
  T get_area() const { return h * w; }
  bool include(const Rect<T> &b) const {
    return ((*this) * b).get_area() == b.get_area();
  }
  bool out(const Rect<T> &b) const {
    return ((*this) * b).get_area() == 0;
  }
};

int n;
vector<int> xs;
vector<int> ys;
Rect<int> rs[30];

int main(void)
{
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    double x, y, h, w;
    scanf("%lf%lf%lf%lf", &x, &y, &h, &w);
    x*=10; y*=10; h*=10; w*=10;
    rs[i] = Rect<int>(x, y, h, w);
    xs.push_back(x); xs.push_back(x+h);
    ys.push_back(y); ys.push_back(y+w);
  }
  sort(xs.begin(), xs.end());
  xs.erase(unique(xs.begin(), xs.end()), xs.end());
  sort(ys.begin(), ys.end());
  ys.erase(unique(ys.begin(), ys.end()), ys.end());
  int ans = 0;
  for (int xi = 0; xi < xs.size() - 1; xi++) {
    int x = xs[xi], h = xs[xi+1] - x;
    for (int yi = 0; yi < ys.size() - 1; yi++) {
      int y = ys[yi], w = ys[yi+1] - y;
      Rect<int> r(x, y, h, w);
      for (int i = 0; i < n; i++) {
        if (rs[i].include(r)) {
          ans += r.get_area();
          break;
        }
      }
    }
  }
  printf(ans % 100 ? "%.2lf\n" : "%.0lf\n", (double)ans / 100);
}
