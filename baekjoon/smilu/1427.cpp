#include <cstdio>
#include <cstring>
#include <algorithm>
#include <functional>

char buf[11];

int main(void)
{
	scanf("%s", buf);
	int len = strlen(buf);
	std::sort(buf, buf + len, std::greater<char>());
	puts(buf);
}