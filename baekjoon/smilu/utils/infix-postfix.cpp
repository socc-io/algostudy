#include <bits/stdc++.h>
using namespace std;

const int prior_map[256] = {
  [(int)'+'] = 1,
  [(int)'-'] = 1,
  [(int)'*'] = 2,
  [(int)'/'] = 2,
  [(int)'^'] = 3,
};

int prior(char ch) {
  return prior_map[(int)ch];
}

string convert_infix_postfix(const string &infix) {
  stack<char> stk;
  stk.push('#');
  string postfix;

  for (auto it = infix.begin(); it != infix.end(); ++it) {
    char ch = (*it);
    if (isalnum(ch)) {
      postfix += ch;
    } else if (ch == '(') {
      stk.push('(');
    } else if (ch == '^') {
      stk.push('^');
    } else if (ch == ')') {
      while (stk.top() != '#' && stk.top() != '(') {
        postfix += stk.top(); stk.pop();
      }
      stk.pop();
    } else {
      if (prior(ch) > prior(stk.top())) {
        stk.push(ch);
      } else {
        while (stk.top() != '#' && prior(ch) <= prior(stk.top())) {
          postfix += stk.top();
          stk.pop();
        }
        stk.push(ch);
      }
    }
  }

  while (stk.top() != '#') {
    postfix += stk.top();
    stk.pop();
  }

  return postfix;
}
