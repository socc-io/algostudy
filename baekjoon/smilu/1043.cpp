#include <cstdio>
#include <vector>
using namespace std;

struct person {
  vector<int> parties;
  bool know;
  bool lock;
};

struct party {
  vector<int> people;
  bool know;
  bool lock;
};

int n, m, k;

person pe[50];
party pa[50];

bool person_know(person* p);
bool party_know(party* pt);

bool person_know(person* p) {
  if (p->know) return true;
  if (p->lock) return false;
  p->lock = true;
  for (auto it = p->parties.begin(); it != p->parties.end(); it++) {
    party* pt = pa + (*it);
    if (party_know(pt)) {
      p->know = true;
      p->lock = false;
      return true;
    }
  }
  p->lock = false;
  return false;
}

bool party_know(party* pt) {
  if (pt->know) return true;
  if (pt->lock) return false;
  pt->lock = true;
  for (auto it = pt->people.begin(); it != pt->people.end(); it++) {
    person* p = pe + (*it);
    if (person_know(p)) {
      pt->know = true;
      pt->lock = false;
      return true;
    }
  }
  pt->lock = false;
  return false;
}

int main(void)
{
  scanf("%d%d%d", &n, &m, &k);
  for (int i = 0; i < k; i++) {
    int tmp; scanf("%d", &tmp); --tmp;
    pe[tmp].know = true;
  }
  for (int i = 0; i < m; i++) {
    int c; scanf("%d", &c);
    for (int j = 0; j < c; j++) {
      int tmp; scanf("%d", &tmp); --tmp;
      pa[i].people.push_back(tmp);
      pe[tmp].parties.push_back(i);
    }
  }
  int cnt = 0;
  for (int i = 0; i < m; i++) {
    if (!party_know(pa+i)) cnt++;
  }
  printf("%d", cnt);
}
