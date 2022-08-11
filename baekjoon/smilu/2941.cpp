#include <iostream>
#include <string>
using namespace std;

const char *dict[] = {
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

bool startsWith(const char *a, const char *b) {
	for (int i = 0; b[i]; i++) {
		if (!a[i] || a[i] != b[i])
			return false;
	}
	return true;
}

int len_word(char *s) {
    for (int i = 0; i < 8; i++) {
        if (startsWith(s, dict[i])) {
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
