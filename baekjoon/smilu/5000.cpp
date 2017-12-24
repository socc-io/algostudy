#include <iostream>
#include <map>

using namespace std;

int N;
int arr[100000];
int indices[100000];

void throw_bread(int pos)
{
	int tmp = arr[pos+2];
	arr[pos+2] = arr[pos+1];
	arr[pos+1] = arr[pos]; 
	arr[pos] = tmp;
}

int main(void)
{
	map<int, int> pos;
	scanf("%d", &N);

	for(int i=0; i<N; ++i) {
		int tmp;
		scanf("%d", &tmp);
		pos[tmp] = i;
	}

	for(int i=0; i<N; ++i) {
		int tmp;
		scanf("%d", &tmp);
		arr[pos[tmp]] = i;
		indices[i] = pos[tmp];
	}

	for(int i=0; i < N - 2; ++i) {
		int cur = N - 1;
		while(arr[cur] != i) --cur;
		while(cur-2 >= i) {
			throw_bread(cur-2);
			cur -= 2;
		}
		if(cur != i) {
			throw_bread(i);
			throw_bread(i);
		}
	}

	if(arr[N-1] == N-1) {
		puts("Possible");
	} else {
		puts("Impossible");
	}
}