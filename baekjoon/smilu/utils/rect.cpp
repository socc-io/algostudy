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