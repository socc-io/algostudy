#include <iostream>

using namespace std;

int checkInside(int cx, int cy, int cr, int x, int y)
{
	int dx = cx - x;
	int dy = cy - y;
	int dx2 = dx * dx;
	int dy2 = dy * dy;
	int ds = dx2 + dy2;
	int cr2 = cr * cr;
	if(ds < cr2) return 1;
	else return 0;
}

int main(int argc, char** argv)
{
	int T;
	int start_x, start_y, end_x, end_y;
	int N;
	int a, b;
	int dcnt;
	cin >> T;
	for(int test_idx=0; test_idx<T; ++test_idx)
	{
		cin >> start_x >> start_y >> end_x >> end_y;
		cin >> N;
		dcnt = 0;
		for(int cidx=0; cidx<N; ++cidx) {
			int x, y, r;
			cin >> x >> y >> r;
			a = checkInside(x, y, r, start_x, start_y);
			b = checkInside(x, y, r, end_x,   end_y);
			if(a != b) dcnt++;
		}
		printf("%d\n", dcnt);
	}

	return 0;
}