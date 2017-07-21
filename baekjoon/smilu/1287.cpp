#include <cstdio>
#include <stack>

using namespace std;

#define INF (0x7FFFFFFF)

char infix[1001];
char postfix[1001];

int postfix_len = 0;

long long calculate(long long a, long long b, char op)
{
	if(op == '+') return a + b;
	else if(op == '-') return a - b;
	else if(op == '*') return a * b;
	else if(op == '/') return a / b;
	// fprintf(stderr, "calculate error: %c\n", op);
	return a + b;
}

int get_prior(char ch)
{
	if(ch == '*') return 2;
	else if(ch == '/') return 2;
	else if(ch == '+') return 1;
	else if(ch == '-') return 1;
	// fprintf(stderr, "get_prior error: %c\n", ch);
	return 1;
}

int infix_to_postfix()
{
	stack<char> S;

	for(char* ch = infix; (*ch) != '\0'; ++ch) {
		char sym = *ch;
		if('0' <= sym && sym <= '9') {
			postfix[postfix_len++] = sym;
		} else if(sym == '(') {
			S.push(sym);
		} else if(sym == ')') {
			while(1)
			{
				if(S.empty()) return -1;
				char t = S.top();
				S.pop();
				if(t == '(')
					break;
				else {
					postfix[postfix_len++] = t;
				}
			}
		} else {
			while(1) {
				if(S.empty()) break;
				char t = S.top();
				if(t == '(') break;
				int t_prior = get_prior(t);
				int sym_prior = get_prior(sym);
				if(t_prior >= sym_prior) {
					postfix[postfix_len++] = t;
					S.pop();
				} else {
					break;
				}
			}
			S.push(sym);
		}
	}

	while(!(S.empty())) {
		char t = S.top();
		S.pop();
		postfix[postfix_len++] = t;
	}

	return 0;
}

long long calculate_postfix()
{
	stack<long long> S;
	for(char* ch = postfix; (*ch) != '\0'; ++ch) {
		char sym = *ch;
		if('0' <= sym && sym <= '9') {
			S.push(sym - '0');
		} else {
			if(S.empty()) return INF;
			long long a = S.top(); S.pop();
			if(S.empty()) return INF;
			long long b = S.top(); S.pop();
			if(a == 0 && sym == '/') return INF;
			long long c = calculate(b, a, sym);
			S.push(c);
		}
	}

	if(S.empty()) return INF;
	return S.top();
}

int main(void)
{
	scanf("%s", infix);

	int flag = infix_to_postfix();

	if(flag == -1) {
		printf("ROCK");
		return 0;
	}

	// printf("postfix: %s\n", postfix);

	long long res = calculate_postfix();

	if(res != INF) {
		printf("%lld", res);
	} else {
		printf("ROCK");
	}
}