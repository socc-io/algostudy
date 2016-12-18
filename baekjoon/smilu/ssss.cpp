#include <cstdio>
#include <cstdlib>
#include <ctime>

typedef void (*solution)(int*, int*, int*);

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
		for(int i=0;i<size;++i) {
			arr[i] = val;
		}
	}
	~vector() {
		delete[] arr;
	}
	void push_back(T val)
	{
		arr[siz++] = val;
		if(siz >= cap) {
			cap <<= 1;
			T* new_arr = new T[cap];
			for(int i=0;i<siz;++i) new_arr[i] = arr[i];
			delete[] arr;
			arr = new_arr;
		}
	}
	T& operator[](int idx) {
		return arr[idx];
	}
};

int evaluate(int *people, int *dest, int *p)
{
	int cost_sum = 0;
	int people_cnt[3] = {0};
	for(int i=0;i<10000;++i) {
		if(dest[i] == -1) {
			cost_sum += 10000 * people[i];
		}
		else {
			cost_sum += abs(p[dest[i]] - i);
			people_cnt[dest[i]] += people[i];
			if(people_cnt[dest[i]] > 20000) {
				return -1;
			}
		}
	}
	return cost_sum;
}

void heuristic1(int *people, int *dest, int *p)
{
	
}

void run(int* people, int* dest, int *p)
{
	// ensemble
	solution sols = {heuristic1};
	int sols_len = 1;

	int dest_buf[10000];
	int min_cost = -1;
	for(int i=0;i<sols_len;++i) {
		for(int j=0;j<10000;++j) dest_buf[j] = -1;
		solution sol = sols[i];
		sol(people, dest_buf, p);
		int cost = evaluate(people, dest_buf, p);
		if(cost < min_cost || min_cost == -1) {
			min_cost = cost;
			for(int j=0;j<10000;++j) dest[j] = dest_buf[j];
		}
	}
}

int main(void)
{
	srand((unsigned int)time(NULL));
	clock_t start_tick = clock();
	int eval_mean = 0;
	for(int floor_idx=0; floor_idx<10000; ++floor_idx) {
		int people[10000];
		int dest[10000];
		int p[3];
		for(int i=0;i<10000;++i) {
			people[i] = (rand()%9)+1;
			dest[i] = -1;
		}
		p[0] = (rand()%10000);
		p[1] = (rand()%10000);
		p[2] = (rand()%10000);
		run(people, dest, p);
		int eval = evaluate(people, dest, p);
		eval_mean += eval / 10000;
	}
	clock_t end_tick = clock();
	printf("eval_mean: %d\n", eval_mean);
	printf("time: %.3lfms\n", (double)(end_tick - start_tick));
}