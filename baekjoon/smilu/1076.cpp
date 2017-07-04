#include <cstdio>
#include <cstring>

const char* names[] = {
	"black",
	"brown",
	"red",
	"orange",
	"yellow",
	"green",
	"blue",
	"violet",
	"grey",
	"white"
};

const int values[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
const int times[] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};

int name_to_idx(char* name)
{
	for(int i=0; i<10; ++i) {
		if(strcmp(name, names[i]) == 0)
			return i;
	}
	return -1;
}

int main(void)
{
	char buffer[256];
	int a, b, c;

	scanf("%s", buffer);
	a = name_to_idx(buffer);

	scanf("%s", buffer);
	b = name_to_idx(buffer);

	scanf("%s", buffer);
	c = name_to_idx(buffer);

	printf("%lld", (long long)(values[a] * 10 + values[b]) * times[c]);
}