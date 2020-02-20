#include <cstdio>

int heap[200010];
int heap_size = 0;

void push(int value) {
  heap_size++;
  heap[heap_size] = value;

  int cur = heap_size;
  while(cur != 1 && heap[cur >> 1] < value) {
    heap[cur] = heap[cur >> 1];
    cur >>= 1;
  }
  heap[cur] = value;
}

int pop() {
  if (heap_size == 0) return 0;
  int ret = heap[1];
  int last = heap[heap_size];
  heap_size--;

  int cur = 1;
  while(1) {
    int child = cur << 1;
    if (child > heap_size) break;
    if (child + 1 <= heap_size && heap[child + 1] > heap[child])
      child++;
    
    if (last < heap[child]) {
      heap[cur] = heap[child];
      cur = child;
    } else break;
  }
  heap[cur] = last;

  return ret;
}

int main(void)
{
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    int value; scanf("%d", &value);
    if (value == 0) {
      printf("%d\n", -1 * pop());
    } else {
      push(-1 * value);
    }
  }
}