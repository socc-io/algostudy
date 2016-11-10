#include <iostream>

using namespace std;

int squaresum(int a, int b)
{
	return a*a + b*b;
}

int main(int argc, char** argv)
{
	int x1, y1, x2, y2, r1, r2;
	int T;
	cin >> T;
	for(int testidx=0; testidx<T; ++testidx)
	{
		cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2;
		int dis = squaresum(x2-x1, y2-y1);
		int rq = r1*r1 + 2*r1*r2 + r2*r2; // (r1+r2)**2
		int rw = r1*r1 - 2*r1*r2 + r2*r2;
		if(dis == 0 && r1 == r2) {
			printf("-1\n");
		}
		else if(rq < dis || dis < rw) {
			printf("0\n");
		}
		else if(dis == rq || dis == rw) {
			printf("1\n");
		}
		else {
			printf("2\n");
		}
	}

	return 0;
}