#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

#define NUM_PERSON 200
#define NUM_FOOD 100

int n, k, d;
int lim_food[NUM_FOOD];
int num_food[NUM_FOOD];
int num_foods = 0;
int cookables[NUM_PERSON][NUM_FOOD + 1];
bool cooking[NUM_PERSON][NUM_FOOD];
vector<pair<int,bool>> backward[NUM_FOOD];
int num_cooking[NUM_PERSON];
bool lock[NUM_PERSON];
bool lock2[NUM_FOOD];

bool replace_cook(int f);

void set_backward(int f, int p, bool v) {
  for (int i = 0; i < backward[f].size(); i++) {
    if (backward[f][i].first == p) {
      backward[f][i].second = v;
      return;
    }
  }
}

int find_fi(int p, int f) {
  for (int fi = 0; cookables[p][fi] != -1; fi++) {
    if (cookables[p][fi] == f) return fi;
  }
  return -1;
}

bool connect_food(int p) {
  if (lock[p]) return false;
  lock[p] = true;

  for (int fi = 0; cookables[p][fi] != -1; ++fi) {
    if (cooking[p][fi]) continue;
    int f = cookables[p][fi];
    if (num_food[f] < lim_food[f] || replace_cook(f)) {
      num_cooking[p]++;
      cooking[p][fi] = true;
      num_food[f]++;
      num_foods++;
      set_backward(f, p, true);
      lock[p] = false;
      return true;
    }
  }

  lock[p] = false;
  return false;
}

bool replace_cook(int f) {
  if (lock2[f]) return false;
  lock2[f] = true;

  for (int i = 0; i < backward[f].size(); i++) {
    int p = backward[f][i].first;
    bool v = backward[f][i].second;
    if (!v) continue;
    if (connect_food(p)) {
      int fi = find_fi(p, f);
      num_cooking[p]--;
      cooking[p][fi] = false;
      num_food[f]--;
      num_foods--;
      set_backward(f, p, false);
      lock2[f] = false;
      return true;
    }
  }

  lock2[f] = false;
  return false;
}

bool find_augment() {
  for (int p = 0; p < n; p++) {
    if (num_cooking[p] >= k) continue;
    if (connect_food(p)) return true;
  }
  return false;
}

int main(void)
{
  scanf("%d%d%d", &n, &k, &d);
  for (int i = 0; i < d; i++) {
    scanf("%d", &lim_food[i]);
  }
  for (int i = 0; i < n; i++) {
    int z; scanf("%d", &z);
    int j;
    for (j = 0; j < z; j++) {
      int ft; scanf("%d", &ft); --ft; // food type
      cookables[i][j] = ft;
      backward[ft].push_back(make_pair(i, false));
    }
    cookables[i][j] = -1;
  }
  while (find_augment());
  printf("%d\n", num_foods);
}
