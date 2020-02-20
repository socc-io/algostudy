#include <iostream>
#include <string>
using namespace std;

string original;
string target;
char s[1000000];
int ds[1000000];
int sp = 0;

int main(void)
{
  cin.tie(NULL);
  ios::sync_with_stdio(false);
  cin >> original >> target;

  int depth = 0;
  for (auto it = original.begin(); it != original.end(); it++) {
    char ch = *it;
    s[sp++] = ch;
    if (target[depth] == ch) ++depth;
    else if (target[0] == ch) depth = 1;
    else depth = 0;
    ds[sp] = depth;
    if (depth == target.size()) {
      sp -= target.size();
      depth = ds[sp];
    };
  }
  s[sp] = 0;
  puts(sp ? s : "FRULA");
}
