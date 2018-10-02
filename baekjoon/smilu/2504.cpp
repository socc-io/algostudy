#include <cstdio>
#include <stack>
using namespace std;

enum StackItemType {
	SIT_CHAR = 0,
	SIT_INT,
};

struct StackItem {
	StackItemType type;
	int value;
	StackItem(StackItemType type, int value): type(type), value(value) {}
};

int run(void)
{
	char ch, str[31];
	stack<StackItem> s;
	int sl, r;
	scanf("%30s", str);
	for (char* sch = str; *sch != '\0'; ++sch) {
		ch = *sch;
		switch (ch) {
		case '(':
			s.push(StackItem(SIT_CHAR, '('));
			break;
		case ')':
			sl = 0;
			while (!s.empty() && (s.top().type != SIT_CHAR || s.top().value != '(')) {
				if (s.top().type == SIT_CHAR) return 0;
				sl += s.top().value;
				s.pop();
			}
			if (s.empty()) return 0;
			s.pop();
			s.push(StackItem(SIT_INT, sl == 0 ? 2 : sl * 2));
			break;
		case '[':
			s.push(StackItem(SIT_CHAR, '['));
			break;
		case ']':
			sl = 0;
			while (!s.empty() && (s.top().type != SIT_CHAR || s.top().value != '[')) {
				if (s.top().type == SIT_CHAR) return 0;
				sl += s.top().value;
				s.pop();
			}
			if (s.empty()) return 0;
			s.pop();
			s.push(StackItem(SIT_INT, sl == 0 ? 3 : sl * 3));
			break;
		default:
			break;
		}
	}

	r = 0;
	while (!s.empty()) {
		if (s.top().type != SIT_INT) return 0;
		r += s.top().value;
		s.pop();
	}

	return r;
}

int main(void)
{
	printf("%d", run());

	return 0;
}
