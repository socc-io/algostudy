#include<cstdio>
#include<map>
using namespace std;
inline int readInt() {
	int ret = 0; char ch;
	while((ch = getchar_unlocked()) >= '0' && ch <= '9')
		ret = ret*10 + (ch-'0');
	return ret;
}
int main()
{
	int n = readInt(), val;
	unsigned long long cnt = 0;
	map<int, int> m;
	for(int i=0; i<n; ++i) {
		val = readInt();
		int level = -1;
		auto lo = m.lower_bound(val);
		if(lo != m.end()) level = max(level, lo->second);
		if(lo != m.begin()) {
			--lo;
			level = max(level, lo->second);
		}
		m[val] = level + 1;
		cnt += level + 1;
		printf("%llu\n", cnt);
	}
}
