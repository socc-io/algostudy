#include <cstdio>

bool asc, desc;
int tmp;

int main(void)
{
	for(int i = 1; i <= 8; ++i) {
		scanf("%d", &tmp);
		if(tmp != i) {
			asc = true;
		}
		if(tmp != 9-i) {
			desc = true;
		}
	}
	puts(asc ? desc ? "mixed" : "descending" : "ascending");
}