#include <cstdio>

int main(void)
{
	int a1, a2, b1, b2, c1, c2, d1, d2;
	scanf("%d%d%d%d%d%d%d%d", &a1, &a2, &b1, &b2, &c1, &c2, &d1, &d2);
	int a11 = b1 - a1;
	int a12 = c1 - d1;
	int a21 = b2 - a2;
	int a22 = c2 - d2;
	int b11 = c1 - a1;
	int b21 = c2 - a2;
	int a_det = a22*a11 - a12*a21;
	if(a_det == 0) { printf("0"); return 0; }
	int t11 = a22 * b11 - a12 * b21;
	if(a_det > 0) {
		if(0 < t11 && t11 < a_det) { printf("1"); return 0; }
		else                       { printf("0"); return 0; }
	}
	else {
		if(a_det < t11 && t11 < 0) { printf("1"); return 0; }
		else                       { printf("0"); return 0; }
	}
}