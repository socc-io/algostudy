#include <cstdio>
#include <cmath>
#include <cfloat>
#include <vector>
#include <algorithm>
using namespace std;

typedef double llf;

struct Vector3 {
  llf x, y, z;
  Vector3() {}
  Vector3(llf x, llf y, llf z): x(x),y(y),z(z) {}
  Vector3 operator-(const Vector3 &v) const {
    return Vector3(x-v.x, y-v.y, z-v.z);
  }
  Vector3 operator+(const Vector3 &v) const {
    return Vector3(x+v.x, y+v.y, z+v.z);
  }
  void operator+=(const Vector3 &v) {
    x+=v.x; y+=v.y; z+=v.z;
  }
  void operator-=(const Vector3 &v) {
    x-=v.x; y-=v.y; z-=v.z;
  }
  Vector3 operator/(llf v) const {
    return Vector3(x/v,y/v,z/v);
  }
  bool operator==(const Vector3 &v) const {
    return x==v.x && y==v.y && z==v.z;
  }
  llf dot(const Vector3 &v) const {
    return x*v.x+y*v.y+z*v.z;
  }
  Vector3 cross(const Vector3 &v) const {
    llf a1 = y*v.z - z*v.y;
    llf a2 = z*v.x - x*v.z;
    llf a3 = x*v.y - y*v.x;
    return Vector3(a1,a2,a3);
  }
  llf length() const {
    return sqrt(x*x + y*y + z*z);
  }
  llf length2() const {
    return x*x + y*y + z*z;
  }
  llf angle(const Vector3 &v) const {
    return dot(v)/(length()*v.length());
  }
};

struct Plane {
  Vector3 base;
  Vector3 orth;
  Plane() {}
  Plane(const Vector3 &a, const Vector3 &b, const Vector3 & c) {
    base = a;
    orth = (b-a).cross(c-a);
  }
  int divide(const Vector3 &v) {
    return (v-base).angle(orth) < 0;
  }
};

int n, k;
Vector3 ps[100];

llf test(int r1, int r2, int r3) {
  const Vector3 &a = ps[r1];
  const Vector3 &b = ps[r2];
  const Vector3 &c = ps[r3];

  Plane p(a, b, c);
  vector<bool> up(n);
  Vector3 us(0,0,0), ds(0,0,0);
  int uc=0, dc=0;
  for (int i = 0; i < n; i++) {
    if (i == r1 || i == r2 || i == r3) continue;
    up[i] = p.divide(ps[i]);
    (up[i]?uc:dc)++;
    (up[i]?us:ds) += ps[i];
  }

  static const int dd[8][3] = {
    {0,0,0},
    {0,0,1},
    {0,1,0},
    {0,1,1},
    {1,0,0},
    {1,0,1},
    {1,1,0},
    {1,1,1},
  };
  const int rs[3] = {r1,r2,r3};

  llf ret = DBL_MAX;
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 3; j++) {
      (dd[i][j]?uc:dc)++;
      (dd[i][j]?us:ds)+=ps[rs[j]];
      up[rs[j]] = dd[i][j];
    }

    Vector3 ua = us / uc, da = ds / dc;
    llf cost = 0;
    for (int j = 0; j < n; j++) {
      cost += (ps[j] - (up[j]?ua:da)).length2();
    }
    ret = min(ret, cost);

    for (int j = 0; j < 3; j++) {
      (dd[i][j]?uc:dc)--;
      (dd[i][j]?us:ds)-=ps[rs[j]];
    }
  }

  return ret;
}

int main(void)
{
  scanf("%d%d", &n, &k);
  for (int i = 0; i < n; i++) scanf("%lf%lf%lf", &ps[i].x, &ps[i].y, &ps[i].z);

  if (k == 1) {
    Vector3 s(0,0,0);
    for (int i = 0; i < n; i++) s += ps[i];
    s = s / n;
    llf cost = 0;
    for (int i = 0; i < n; i++) cost += (s-ps[i]).length2();
    printf("%lf\n", cost);
    return 0;
  }

  llf cost = DBL_MAX;
  for (int i = 0; i < n; i++) {
    for (int j = i+1; j < n; j++) {
      for (int k = j+1; k < n; k++) {
        cost = min(cost, test(i, j, k));
      }
    }
  }
  printf("%lf\n", cost == DBL_MAX ? 0 : cost);
}
