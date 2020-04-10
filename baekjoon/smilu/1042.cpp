#include <iostream>
#include <cstdio>
#include <cstring>
#include <map>
using namespace std;

#define MOD 1000000007

int m;
int sl;
char s[2601];
int dp[50][5][5][2600];
char nuc_ids[128];

map<string, int> codon_ids;
map<string, int> ami_ids;
int ami_index;

int get_codon_id(char r1, char r2, char r3) {
  string key;
  key.resize(3);
  key[0] = r1; key[1] = r2; key[2] = r3;
  auto it = codon_ids.find(key);
  if (it == codon_ids.end()) return 0;
  return it->second;
}

template <class T>
void convert_nuc(T s, int l) {
  for (int i = 0; i < l; i++) s[i] = nuc_ids[(int)s[i]];
}

int get_dp(int r1, int r2, int r3, int r4) {
  int &r = dp[r1][r2][r3][r4];
  if (r != -1) return r;
  r = 0;
  if (r2 == 0) {
    if (r3 == 0) {
      if (r4 >= sl - 2) {
        return r = 1;
      }
      r += get_dp(r1, 0, 0, r4 + 1); // kill
      r += get_dp(r1, 0, s[r4], r4 + 1);
    } else {
      if (r4 >= sl - 1) {
        return r = 1;
      }
      if (r2 != s[r4]) r += get_dp(r1, 0, r3, r4 + 1); // kill
      r += get_dp(r1, r3, s[r4], r4 + 1);
    }
  } else {
    if (r4 >= sl) {
      return r = 1;
    }
    if (r3 != s[r4]) r += get_dp(r1, r2, r3, r4 + 1); // kill
    int cid = get_codon_id(r2, r3, s[r4]);
    r += get_dp(cid, 0, 0, r4 + 1);
  }
  printf("%d, %d, %d, %d: %d\n", r1, r2, r3, r4, r);
  r %= MOD;
  return r;
}

int main()
{
  memset(dp, 0xFF, sizeof(dp));

  nuc_ids[(int)'A'] = 1;
  nuc_ids[(int)'T'] = 2;
  nuc_ids[(int)'G'] = 3;
  nuc_ids[(int)'C'] = 4;

  scanf("%s%d", s, &m);
  sl = strlen(s);
  convert_nuc(s, sl);

  ami_index = 1;
  for (int i = 0; i < m; i++) {
    string codon, ami;
    cin >> codon >> ami;
    convert_nuc(codon, 3);
    if (ami_ids.find(ami) == ami_ids.end()) {
      ami_ids[ami] = ami_index;
      codon_ids[codon] = ami_index++;
    } else {
      codon_ids[codon] = ami_ids[ami];
    }
  }

  printf("%d\n", get_dp(0, 0, 0, 0));
}
