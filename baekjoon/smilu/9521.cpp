#include <cstdio>

#define MOD 1000000007

typedef unsigned long long ull;

struct Node
{
	int next;
	bool inLoop;
	int loop_size;
	int starting;
};

Node nodes[1000001];
ull n, k;

void set_loop(int pos, int loop_idx)
{
	if(nodes[pos].inLoop) return;
	nodes[pos].inLoop = true;
	(nodes[loop_idx].loop_size)++;
	set_loop(nodes[pos].next, loop_idx);
}

void loop_check_visit(int pos, bool* visited, int starting)
{
	if(visited[pos]) return;
	visited[pos] = true;
	int next = nodes[pos].next;
	if(visited[next]) {
		if(nodes[next].starting == starting || next == pos) {
			set_loop(next, next);
		}
	}
	else {
		nodes[pos].starting = starting;
		loop_check_visit(next, visited, starting);
	}
}

void loop_check()
{
	bool visited[1000001] = {};
	for(int i=0;i<n;++i) {
		loop_check_visit(i, visited, i);
	}
}

ull special_function_mem[1000001] = {};

ull special_function(int x)
{
	if(special_function_mem[x] == -1) {
		special_function_mem[x] = (((special_function(x-2) * (k-1)) % MOD) + ((special_function(x-1) * (k-2)) % MOD)) % MOD;
	}
	return special_function_mem[x];
}

ull prod()
{
	ull result = 1;
	for(int i=0;i<n;++i) {
		if(nodes[i].inLoop) {
			if(nodes[i].loop_size) {
				result *= special_function(nodes[i].loop_size);
				result %= MOD;
			}
		}
		else {
			result *= k-1;
			result %= MOD;
		}
	}
	return result;
}

int main(void)
{
	scanf("%lld%lld", &n, &k);
	for(int i=0;i<n;++i) {
		int tmp_val;
		scanf("%d", &tmp_val);
		--tmp_val;
		nodes[i].next = tmp_val;
		nodes[i].starting = -1;
		nodes[i].inLoop = false;
		nodes[i].loop_size = 0;
	}
	loop_check();
	for(int i=0;i<1000001;++i) {
		special_function_mem[i] = -1;
	}
	special_function_mem[1] = k % MOD;
	special_function_mem[2] = (k * (k-1)) % MOD;
	special_function_mem[3] = (special_function_mem[2] * (k-2)) % MOD;
	printf("%llu", prod());
}
