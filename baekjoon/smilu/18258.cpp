#include <cstdio>
#include <cstring>

class queue {
  int v[2000020];
  int left = 0;
  int right = 0;
public:
  void push(int x) {
    v[right++] = x;
  }
  int pop() {
    if (left == right) return -1;
    ++left;
    return v[left-1];
  }
  int size() { return right - left; }
  bool empty() { return left == right; }
  int front() {
    if (empty()) return -1;
    return v[left];
  }
  int back() {
    if (empty()) return -1;
    return v[right-1];
  }
};

queue q;

int main(void)
{
  int t; scanf("%d", &t);
  while (t--) {
    char cmd[10];
    scanf("%s", cmd);
    if (!strcmp(cmd, "push")) {
      int x; scanf("%d", &x);
      q.push(x);
    } else if (!strcmp(cmd, "pop")) {
      printf("%d\n", q.pop());
    } else if (!strcmp(cmd, "size")) {
      printf("%d\n", q.size());
    } else if (!strcmp(cmd, "empty")) {
      printf("%d\n", q.empty());
    } else if (!strcmp(cmd, "front")) {
      printf("%d\n", q.front());
    } else if (!strcmp(cmd, "back")) {
      printf("%d\n", q.back());
    } 
  }
}
