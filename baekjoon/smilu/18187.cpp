#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll n;

int main() {
  cin >> n;
  ll a = n/3, b = n/3, c = n/3;
  if (n%3 == 2) {
    ++a, ++b;
  } else if (n%3 == 1) {
    ++a;
  }
  cout << (a+c+1)*(b+1)+a*c << '\n';
}
