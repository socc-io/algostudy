#include <iostream>
#include <string>
using namespace std;

char *dict[] = {
	"c=",
	"c-",
	"dz=",
	"d-",
	"lj",
	"nj",
	"s=",
	"z=",
};

int len_dict[] = {
	2, 2, 3, 2, 2, 2, 2, 2,
};

bool is_prefix_same(char *a, char *b) {
	int i = 0;
	while (a[i] != 0 && b[i] != 0) {
		if (a[i] != b[i])
			return false;
		i++;
	}
	return true;
}

int len_word(char *s) {
	for (int i = 0; i < 8; i++) {
		if (is_prefix_same(s, dict[i])) {
			return len_dict[i];
		}
	}
	return 1;
}

int main() {
	char s[101];
	cin >> s;

	int i = 0, count = 0;
	while (s[i]) {
		i += len_word(s + i);
		count++;
	}

	cout << count;
}
