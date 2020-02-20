#include <iostream>
#include <vector>
#include <string>
#include <stack>
using namespace std;

int priority(char op) {
  if (op == '*' || op == '/') return 2;
  if (op == '+' || op == '-') return 1;
  return 0;
}

string convert(string input) {
  string res;
  stack<char> ops;
  
  for (int i = 0; i < input.size(); i++) {
    char ch = input[i];
    if ('A' <= ch && ch <= 'Z') res.push_back(ch);
    else {
      if (ch == '(') ops.push(ch);
      else if (ch == ')') {
        while (!ops.empty() && ops.top() != '(') {
          res.push_back(ops.top());
          ops.pop();
        }
        if (!ops.empty()) ops.pop();
      } else {
        while (!ops.empty() && priority(ops.top()) >= priority(ch)) {
          res.push_back(ops.top());
          ops.pop();
        }
        ops.push(ch);
      }
    }
  }
  
  while(!ops.empty()) {
    res.push_back(ops.top());
    ops.pop();
  }

  return res;
}

int main(void)
{
  string input;
  cin >> input;
  cout << convert(input);
}