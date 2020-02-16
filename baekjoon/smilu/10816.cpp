#include <cstdio>
#include <map>
using namespace std;

int main(void)
{
  map<int, int> counter;
  int N, M;
  scanf("%d", &N);
  
  for (int i = 0; i < N; i++) {
    int num;
    scanf("%d", &num);
    if (counter.find(num) == counter.end()) {
      counter[num] = 1;
    } else {
      counter[num] += 1;
    }
  }

  scanf("%d", &M);
  for (int i = 0; i < M; i++) {
    int target;
    scanf("%d", &target);
    if (counter.find(target) == counter.end()) {
      printf("0 ");
    } else {
      printf("%d ", counter[target]);
    }
  }
}
