#include <map>

int main(void)
{
	std::map<int, int> m;
	printf("%d\n", m.find(1) == m.end());
	printf("%d\n", m[1]);
	printf("%d\n", m.find(1) == m.end());
}