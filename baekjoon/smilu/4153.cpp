#include <cstdio>
#include <cstdlib>

int compare(const void *pa, const void *pb) {
	int a = *((int*)pa);
	int b = *((int*)pb);
	if (a > b) return 1;
	if (a == b) return 0;
	return -1;
}

int sqr(int x) { return x*x; }

int solve(int a, int b, int c) {
	int arr[3] = {a, b, c};
	qsort(arr, 3, sizeof(int), compare);
	return sqr(arr[0])+sqr(arr[1]) == sqr(arr[2]);
}

int main() {
	int a, b, c;
	while (1) {
		scanf("%d %d %d", &a, &b, &c);
		if (!a || !b || !c) break;
		if (solve(a, b, c)) {
			puts("right");
		} else {
			puts("wrong");
		}
	}
	return 0;
}
