#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;

int T, N;
string str1, str2;

map<string, vector<string> > clothes;

int main(void)
{
	int T, N;
	string str1, str2;
	scanf("%d", &T);
	for(int t = 0; t < T; ++t) {
		clothes.clear();
		scanf("%d", &N);
		for(int i = 0; i < N; ++i) {
			cin >> str1 >> str2;
			clothes[str2].push_back(str1);
		}
		int ans = 1;
		for(auto it = clothes.begin(); it != clothes.end(); ++it) {
			ans *= it->second.size() + 1;
		}
		printf("%d\n", ans-1);
	}
}