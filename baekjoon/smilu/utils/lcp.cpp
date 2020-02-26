#include <vector>
#include <string>
#include <algorithm>
using namespace std;

typedef vector<int> vi;

vi get_lcp(string str, vi sa) {
  /*
  Get longest common prefix array
  */
  int n = sa.size(), len = 0;
  vi r(n), lcp(n);
  for (int i = 0; i < n; i++) r[sa[i]] = i;
  for (int i = 0; i < n; i++) {
    int k = r[i];
    if (k) {
      int j = sa[k-1];
      while (str[j+len] == str[i+len]) ++len;
      lcp[k] = len;
      if (len) -- len;
    }
  }
  return lcp;
}