#include <iostream>
#include <cstdlib>

using namespace std;

typedef struct _pat{
	char bit[31];
	int count;
	int one;
}PAT;

int max_one;
int max_n;

void extend_pat(PAT* src, PAT* dst, char bit){
	dst->count = src->count;
	dst->one = src->one;
	for (int i = 0; i < src->count; i++){
		dst->bit[i] = src->bit[i];
	}
	dst->bit[dst->count++] = bit;
	dst->bit[dst->count] = NULL;
	if (bit == '1') dst->one++;
}


void patter(PAT* p){
	if (p->one == max_one){
		for (int i = p->count; i < max_n; i++){
			p->bit[i] = '0';
		}
		p->bit[max_n] = NULL;
		cout << p->bit << endl;
	}
	else if (p->count >= max_n){
		return;
	}else{
		PAT* c0 = (PAT*)malloc(sizeof(PAT));
		PAT* c1 = (PAT*)malloc(sizeof(PAT));
		extend_pat(p, c0, '1');
		extend_pat(p, c1, '0');
		patter(c0);
		patter(c1);
	}
	free(p);
}

int main(void){
	cin >> max_n >> max_one;
	PAT* first = (PAT*)malloc(sizeof(PAT));
	
	first->count = 0;
	first->one = 0;
	for (int i = 0; i < max_n; i++){
		first->bit[i] = '0';
	}
	first->bit[max_n] = NULL;
	patter(first);
	return 0;
}
