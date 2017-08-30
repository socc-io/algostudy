#include <cstdio>
#include <vector>

using namespace std;

char buf[31];

int is_set(char a, char b)
{
	if(a == '(' && b == ')') return 2;
	if(a == '[' && b == ']') return 3;
	return 0;
}

struct Item
{
	char ch;
	int val;
	Item(char ch, int val): ch(ch), val(val) {}
};

struct AA
{
	vector<Item> S;
	void merge_val()
	{
		int size;
		while((size = S.size()) >= 2 && S[size-1].ch == 0 && S[size-2].ch == 0) {
			int tmp = S[size-1].val + S[size-2].val;
			S.pop_back();
			S.pop_back();
			S.push_back(Item(0, tmp));
		}
	}
	bool push_ch(char ch)
	{
		if(ch == '(' || ch == '[') {
			S.push_back(Item(ch, 0));
			return true;
		}
		int tmp;
		Item last = S.back();
		if(last.ch == 0) {
			if((tmp = is_set(S[S.size() - 2].ch, ch))) {
				S.pop_back();
				S.pop_back();
				S.push_back(Item(0, last.val * tmp));
				merge_val();
				return true;
			} else return false;
		}
		else {
			if((tmp = is_set(last.ch, ch))) {
				S.pop_back();
				S.push_back(Item(0, tmp));
				merge_val();
				return true;
			} else return false;
		}
	}
};

int main(void)
{
	scanf("%s", buf);
	AA a;
	bool succ = true;

	for(char* ch = buf; *ch != '\0'; ++ch) {
		if(!a.push_ch(*ch)) {
			succ = false;
			break;
		}
	}

	int ans = 0;
	for(auto it = a.S.begin(); it != a.S.end(); ++it) {
		if(it->val == 0) {
			succ = false;
			break;
		}
		ans += it->val;
	}

	printf("%d", succ ? a.S[0].val : 0);
}