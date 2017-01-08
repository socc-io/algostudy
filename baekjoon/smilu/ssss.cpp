#include <cstdio>
#include <cstdlib>
#include <ctime>

typedef void(*solution)(int*, int*, int*);
#define INF 0x3FFFFFFF

void sort3(int *arr)
{
	int tmp;
	if (arr[0] > arr[1]) {
		tmp = arr[0];
		arr[0] = arr[1];
		arr[1] = tmp;
	}
	if (arr[1] > arr[2]) {
		tmp = arr[1];
		arr[1] = arr[2];
		arr[2] = tmp;
	}
}

template <class T, class F> void merge_sort(T *arr, int len, F comparator)
{
	if (len < 16) { // bubble sort
		for (int i = 0; i<len - 1; ++i) {
			for (int j = 0; j<len - i - 1; ++j) {
				if (comparator(arr[j + 1], arr[j])) {
					T tmp = arr[j];
					arr[j] = arr[j + 1];
					arr[j + 1] = tmp;
				}
			}
		}
		return;
	}
	int p = len / 2;
	merge_sort(arr, p, comparator);
	merge_sort(arr + p, len - p, comparator);
	T *n = new T[len];
	int i, j, k;
	for (i = 0, j = p, k = 0; i<p&&j<len;) n[k++] = comparator(arr[i], arr[j]) ? arr[i++] : arr[j++];
	while (i<p)   n[k++] = arr[i++];
	while (j<len) n[k++] = arr[j++];
	for (i = 0; i<len; ++i) arr[i] = n[i];
	delete[] n;
}

template <class A, class B> struct pair
{
	A first;
	B second;
};

template <class A, class B, class C> struct triplet
{
	A first;
	B second;
	C third;
};

template <class T> class vector
{
public:
	T* arr;
	int cap;
	int siz;
	vector() {
		int cap = 100;
		arr = new T[cap];
		siz = 0;
	}
	vector(int size) {
		int cap = size;
		arr = new T[cap];
		siz = size;
	}
	vector(int size, T val) {
		int cap = size;
		arr = new T[cap];
		siz = size;
		for (int i = 0; i<size; ++i) {
			arr[i] = val;
		}
	}
	~vector() {
		delete[] arr;
	}
	void reserve(int size)
	{
		if (size > cap) {
			cap = size;
			T *new_arr = new T[cap];
			for (int i = 0; i<siz; ++i) new_arr[i] = arr[i];
			delete[] arr;
			arr = new_arr;
		}
	}
	void push_back(T val)
	{
		arr[siz++] = val;
		if (siz >= cap) {
			reserve(cap << 1);
		}
	}
	void pop_back() { --siz; }
	T front() { return arr[0]; }
	T back() { return arr[siz - 1]; }
	int find(T val)
	{
		for (int i = 0; i<siz; ++i) {
			if (arr[i] == val) return i;
		}
		return -1;
	}
	void fill(T val)
	{
		for (int i = 0; i<siz; ++i) {
			arr[i] = val;
		}
	}
	T& operator[](int idx) {
		return arr[idx];
	}
};

template <class T> class deque
{
public:
	T *arr;
	int front;
	int back;
	int cap;
	deque() {
		front = 0;
		back = 1;
		cap = 10;
		arr = new T[cap];
	}
	~deque() {
		delete[] arr;
	}
	int find(T val)
	{
		for (int i = front; i != back; i = (i + 1) % cap) {
			if (arr[i] == val) return (i + cap - front) % cap;
		}
		return -1;
	}
	void push_back(T val) {
		arr[back] = val;
		back = (back + 1) % val;
		if (front == back) {
			T *narr = new T[cap << 1];
			for (int i = 0; i<cap; ++i) {
				narr[i] = arr[(front + i) % cap];
			}
			delete[] arr;
			arr = narr;
			front = 0;
			back = cap;
			cap <<= 1;
		}
	}
	void pop_front() {
		++front;
	}
	int size() {
		if (back < front) {
			return back + cap - front;
		}
		else {
			return back - front;
		}
	}
	T& operator[](int idx) {
		return arr[(front + idx) % cap];
	}
};

int evaluate(int *people, int *dest, int *p)
{
	int cost_sum = 0;
	int people_cnt[3] = { 0 };
	for (int i = 0; i<10000; ++i) {
		if (i == p[0] || i == p[1] || i == p[2]) continue;
		if (dest[i] == -1) {
			cost_sum += 10000;
		}
		else {
			cost_sum += abs(p[dest[i]] - i);
			people_cnt[dest[i]] += people[i];
			if (people_cnt[dest[i]] > 20000) {
				return -1;
			}
		}
	}
	printf("D: ");
	for (int i = 0; i < 10000; i += 300) {
		printf("%d ", dest[i]);
	}
	printf("%d(%d), %d(%d), %d(%d)", p[0], people_cnt[0], p[1], people_cnt[1], p[2], people_cnt[2]);
	printf("\n");
	return cost_sum;
}

void heuristic1(int *people, int *dest, int *p)
{
	int left_cur = 0, right_cur = 9999;
	int cur;
	int p_cnt[3] = { 0 };
	for (; left_cur<p[0]; ++left_cur) {
		p_cnt[0] += people[left_cur];
		dest[left_cur] = 0;
		if (p_cnt[0] > 20000) {
			p_cnt[0] -= people[left_cur];
			dest[left_cur] = -1;
			break;
		}
	}
	for (; right_cur>p[2]; --right_cur) {
		p_cnt[2] += people[right_cur];
		dest[right_cur] = 2;
		if (p_cnt[2] > 20000) {
			p_cnt[2] -= people[right_cur];
			dest[right_cur] = -1;
			break;
		}
	}
	int middle_point = (left_cur + right_cur) / 2;
	for (cur = left_cur; cur <= right_cur; ++cur) {
		if (cur == p[0] || cur == p[1] || cur == p[2]) continue;
		int dst[3];
		for (int i = 0; i<3; ++i) {
			dst[i] = abs(cur - p[i]);
		}
		int prior[3] = { 0,1,2 };
		if (dst[prior[0]] > dst[prior[1]]) {
			int tmp = prior[0];
			prior[0] = prior[1];
			prior[1] = tmp;
		}
		if (dst[prior[1]] > dst[prior[2]]) {
			int tmp = prior[1];
			prior[1] = prior[2];
			prior[2] = tmp;
		}
		for (int i = 0; i<3; ++i) {
			int p_idx = prior[i];
			if (p_cnt[p_idx] + people[cur] <= 20000) {
				p_cnt[p_idx] += people[cur];
				dest[cur] = p_idx;
				break;
			}
		}
	}
}

void heuristic3(int *people, int *dest, int *p)
{
	bool matched[10000] = { 0 };
	int match_cnt = 0;
	int p_count[3] = { 0 };
	for (int i = 0; i<10000; ++i) {
		for (int j = 0; j < 3; ++j) {
			int cur = p[j] - i;
			if (cur == p[0] || cur == p[1] || cur == p[2]) continue;
			if (0 <= cur && cur < 10000 && !matched[cur]) {
				if (p_count[j] + people[cur] <= 20000) {
					matched[cur] = true;
					dest[cur] = j;
					++match_cnt;
					p_count[j] += people[cur];
				}
			}
			cur = p[j] + i;
			if (cur == p[0] || cur == p[1] || cur == p[2]) continue;
			if (0 <= cur && cur < 10000 && !matched[cur]) {
				if (p_count[j] + people[cur] <= 20000) {
					matched[cur] = true;
					dest[cur] = j;
					++match_cnt;
					p_count[j] += people[cur];
				}
			}
		}
		if (match_cnt >= 9997) break;
	}
}

void ensemble(int* people, int* dest, int *p)
{
	// ensemble
	solution sols[] = { heuristic1 };
	int sols_len = 1;

	int dest_buf[10000];
	int min_cost = -1;
	for (int i = 0; i<sols_len; ++i) {
		for (int j = 0; j<10000; ++j) dest_buf[j] = -1;
		solution sol = sols[i];
		sol(people, dest_buf, p);
		int cost = evaluate(people, dest_buf, p);
		if (cost < min_cost || min_cost == -1) {
			min_cost = cost;
			for (int j = 0; j<10000; ++j) dest[j] = dest_buf[j];
		}
	}
}

void make_random(int *people, int *dest, int *p)
{
	for (int i = 0; i<10000; ++i) {
		people[i] = (rand() % 9) + 1;
		dest[i] = -1;
	}
	p[0] = (rand() % 10000);
	do {
		p[1] = (rand() % 10000);
	} while (p[1] == p[0]);
	do {
		p[2] = (rand() % 10000);
	} while (p[2] == p[1] || p[2] == p[0]);
	sort3(p);
}

int main(void)
{
	int people[10000];
	int dest[10000];
	int p[3];
	solution run = heuristic3;
	srand((unsigned int)time(NULL));
	clock_t start_tick = clock();
	int eval_mean = 0;
	for (int floor_idx = 0; floor_idx<10000; ++floor_idx) {
		if (floor_idx % 1000 == 0) {
			printf("progress: %d %% \n", (floor_idx / 100));
		}
		make_random(people, dest, p);
		run(people, dest, p);
		int eval = evaluate(people, dest, p);
		eval_mean += eval / 10000;
	}
	clock_t end_tick = clock();
	printf("eval_mean: %d\n", eval_mean / 9997);
	printf("time: %.3lfms\n", (double)(end_tick - start_tick));
}