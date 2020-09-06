#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int l, m, n;

struct Zipper: public vector<int> {
  void run() {
    sort(begin(), end());
    erase(unique(begin(), end()), end());
  }
  int index(int v) {
    return lower_bound(begin(), end(), v) - begin();
  }
} yz;

struct Route {
  int n;
  pair<int,int> ths[200020];
  int y_end;
  void input(int n) {
    this->n = n;
    int ti = 0;
    int a, b; cin >> a >> b;
    ths[ti++] = make_pair(0, a);
    int cx = a;
    int cy = b;
    for (int i = 1; i < n; i++) {
      cin >> a >> b;
      ths[ti++] = make_pair(cy, cx + a);
      cx += a;
      cy += b;
    }
    y_end = cy;
  }
  pair<int,int> get_x(int y) {
    auto it = lower_bound(ths, ths+n, make_pair(y, -0x3f3f3f3f));
    if (it->first == y) {
      return make_pair(it->second, it == ths ? it->second : (it-1)->second);
    }
    return make_pair(it->second, 0x3f3f3f3f);
  }
  void sym_move(int x, int y) {
    int ti = lower_bound(ths, ths+n, make_pair(y, -0x3f3f3f3f)) - ths;
    for (int i = ti; i < n; i++) {
      ths[i].second = (x<<1) - ths[i].second;
    }
  }
} L, R, C;

int get_right_x(int y) {
  auto it = lower_bound(R.ths, R.ths + R.n, make_pair(y, -0x3f3f3f3f));
  if (it->first == y) {
    if (it == R.ths) return it->second;
    return max(it->second, (it-1)->second);
  }
  return (it-1)->second;
}

int get_left_x(int y) {
  auto it = lower_bound(L.ths, L.ths + L.n, make_pair(y, -0x3f3f3f3f));
  if (it->first == y) {
    if (it == L.ths) return it->second;
    return min(it->second, (it-1)->second);
  }
  return (it-1)->second;
}

int get_inner() {
  int earn = 0;

  for (int i = 0; i < C.n; i++) {
    const int yb = C.ths[i].first;
    const int ye = i == C.n - 1 ? C.y_end : C.ths[i+1].first;
    const int ib = yz.index(yb), ie = yz.index(ye);
    const int cx = C.ths[i].second;
    bool prev_in = false;
    int prev_in_y = -1;
    for (int yi = ib; yi <= ie; yi++) {
      const int y = yz[yi];
      int lx = get_left_x(y);
      int rx = get_right_x(y);
      if (lx <= cx && cx <= rx) {
        if (prev_in) {
          earn += y - prev_in_y;
        } else {
          prev_in = true;
        }
        prev_in_y = y;
      } else {
        prev_in = false;
      }
    }
  }

  return earn;  
}

int solve() {
  cin >> l >> m >> n;
  L.input(l);
  R.input(m);
  C.input(n);

  yz.clear();
  yz.reserve(100000);
  yz.push_back(0);
  for (int i = 0; i < l; i++) yz.push_back(L.ths[i].first);
  for (int i = 0; i < m; i++) yz.push_back(R.ths[i].first);
  for (int i = 0; i < n; i++) yz.push_back(C.ths[i].first);
  yz.push_back(L.y_end);
  yz.run();

  int ans = get_inner();

  for (int i = 0; i < C.n-1; i++) {
    const int y = C.ths[i+1].first;
    int xb = C.ths[i].second;
    int xe = C.ths[i+1].second;
    if (xb > xe) swap(xb, xe);
    for (int x = xb; x <= xe; x++) {
      C.sym_move(x, y);
      ans = max(ans, get_inner());
      C.sym_move(x, y);
    }
  }

  return ans;
}

int main(int argc, char** argv)
{
  setbuf(stdout, NULL);
	int T, test_case;

	cin >> T;
	for(test_case = 0; test_case  < T; test_case++)
	{
		cout << "Case #" << test_case+1 << endl;
		cout << solve() << endl;
	}

	return 0;
}