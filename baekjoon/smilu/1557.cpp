#include <cstdio>

typedef long long ll;

const int MAX = 100010;

int mob[MAX];

ll f(ll x) {
  ll ret = 0;
  for (int i = 1; i*i <= x; i++)
    ret += mob[i] * (x/(i*i));
  return ret;
}

void set_mob() {
  for (int i = 0; i < MAX; i++) mob[i] = 1;
  for (int i = 2; i*i < MAX; i++) {
    if (mob[i] != 1) continue;
    for (int j = i; j < MAX; j += i) mob[j] *= -i;
    for (int j = i*i; j < MAX; j += i*i) mob[j] = 0;
  }
  for (int i = 2; i < MAX; i++) {
         if (mob[i] ==  i) mob[i] =  1;
    else if (mob[i] == -i) mob[i] = -1;
    else if (mob[i] <   0) mob[i] =  1;
    else if (mob[i] >   0) mob[i] = -1;
  }
}

int main(void)
{
  ll k; scanf("%lld", &k);
  set_mob();

  ll s = 1, e = 2000000000;
  while (s < e) {
    ll m = (s+e)>>1;
    ll v = f(m);
    if (v > k) e = m-1;
    else if (v < k) s = m+1;
    else e = m;
  }
  printf("%lld\n", s);
}
