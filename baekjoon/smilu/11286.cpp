#include <cstdio>
#include <vector>
using namespace std;

typedef pair<int, int> pii;

pii heap[200010];
int heap_size = 0;

void push(pii value) {
  heap_size++;
  heap[heap_size] = value;

  int cur = heap_size;
  while(cur != 1 && heap[cur >> 1] < value) {
    heap[cur] = heap[cur >> 1];
    cur >>= 1;
  }
  heap[cur] = value;
}

pii pop() {
  if (heap_size == 0) return make_pair(0, 0);
  pii ret = heap[1];
  pii last = heap[heap_size];
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

pii zip(int value) {
  int key = value > 0 ? -value : value;
  return make_pair(key, -value);
}

int main(void)
{
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    int value; scanf("%d", &value);
    pii v = zip(value);
    if (value == 0) {
      printf("%d\n", -pop().second);
    } else {
      push(v);
    }
  }
}