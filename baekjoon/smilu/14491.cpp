#include <cstdio>

#define BASE 9

template <class T>
inline void swap(T* a, T* b)
{
	T tmp; 
	tmp = *a;
	*a = *b;
	*b = tmp;
}

int main(void)
{
	int a, i;
	char res[20];
	scanf("%d", &a);
	for(i=0; a; ++i) {
		res[i] = (a%BASE) + (int)'0';
		a /= BASE;
	}
	res[i] = '\0';
	int len = i;
	int mid = i>>1;
	for(; i>=mid; --i) {
		swap(res+i, res+(len-1-i));
	}
	printf("%s", res);
	return 0;
}