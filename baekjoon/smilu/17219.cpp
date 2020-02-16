#include <iostream>
#include <map>
#include <string>
using namespace std;

int main(void)
{
  cin.tie(NULL);
  ios::sync_with_stdio(false);

  int N, M;
  map<string, string> dict;
  cin >> N >> M;

  for (int i = 0; i < N; i++) {
    string key, value;
    cin >> key >> value;
    dict[key] = value;
  }

  for (int i = 0; i < M; i++) {
    string key;
    cin >> key;
    cout << dict[key] << '\n';
  }
}