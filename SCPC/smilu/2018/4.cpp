/*
You should use the statndard input/output

in order to receive a score properly.

Do not use file input and output

Please be very careful. 
*/

#include <iostream>
#include <vector>
#include <list>
#include <map>

using namespace std;

int gcd(int a, int b)
{
	if(b == 0) return a;
	int tmp = a % b;
	return gcd(b, tmp);
}

struct Point
{
	int x;
	int y;

	bool operator==(const Point& p) {
		return x == p.x && y == p.y;
	}
	Point operator+(const Point& p) {
		Point res;
		res.x = x + p.x;
		res.y = y + p.y;
		return res;
	}
	Point operator-(const Point& p) {
		Point res;
		res.x = x - p.x;
		res.y = y - p.y;
		return res;
	}
	bool operator<(const Point& p) const {
		if(x < p.x) return 1;
		if(x > p.x) return 0;
		if(y < p.y) return 1;
		return 0;
	}
};

struct Line
{
	Point from;
	Point to;

	int parallel(Point a, Point b)
	{
		return (to.y - from.y) * (b.x - a.x) == (b.y - a.y) * (to.x  - from.x);
	}
};

int Answer;

int N;
Point points[50000];
Line lines[50000];
map<Point, int> check_mem;

int is_mid(int a, int b, int c)
{
	if(a < b) {
		if(a <= c && c <= b) return 1;
		else return 0;
	} else {
		if(b <= c && c <= a) return 1;
		return 0;
	}
}

int line_collision(Point a, Point b, Point c, Point d)
{
	int dy_ab = a.y - b.y;
	int dx_ab = a.x - b.x;
	int dy_cd = c.y - d.y;
	int dx_cd = c.x - d.x;
	int B_x = (a.x * dy_ab * dx_cd) - (c.x * dy_cd * dx_ab) + (c.y - a.y) * dx_ab * dx_cd;
	int A_x = dy_ab - dy_cd;
	int B_y = B_x * dy_ab - a.x * dy_ab * A_x + a.y * A_x * dx_ab;
	int A_y = dx_ab * A_x;

	if(is_mid(c.x*A_x, d.x*A_x, B_x) && is_mid(c.y*A_y, d.y*A_y, B_y)) return 1;

	return 0;
}

int check(Point offset)
{
	for(int i=0; i<N; ++i) {  // index of start point
		int col_line_num = 0;
		for(int j=0; j<N; ++j) {  // index of line
			Point po = points[i] + offset;
			int res = line_collision(points[i], po, lines[j].from, lines[j].to);
			if(!(lines[j].parallel(points[i], po))) {
				col_line_num++;
			}
		}
		if(col_line_num != 2 && col_line_num != 4) {
			return 0;
		}
	}
	return 1;
}

int do_task()
{
	cin >> N;
	for(int i=0; i<N; ++i) {
		cin >> points[i].x >> points[i].y;
	}
	for(int i=0; i<N-1; ++i) {
		lines[i].from = points[i];
		lines[i].to = points[i+1];
	}
	lines[N-1].from = points[N-1];
	lines[N-1].to = points[0];

	check_mem.clear();

	for(int i=0; i<N; ++i) {
		for(int j=i+2; j<N; ++j) {
			if(i == 0 && j == N-1) continue;

			Point offset = points[j] - points[i];
			if(offset.x == 0) offset.y = 1;
			if(offset.y == 0) offset.x = 1;
			if(offset.x < 0) {
				offset.x *= -1;
				offset.y *= -1;
			}
			int g = gcd(offset.x, offset.y);
			offset.x /= g;
			offset.y /= g;

			if(check_mem.find(offset) == check_mem.end()) {
				check_mem[offset] = 1;
				if(check(offset)) return 1;
			}
		}
	}

	return 0;
}

int main(int argc, char** argv)
{
	int T, test_case;
	/*
	   The freopen function below opens input.txt file in read only mode, and afterward,
	   the program will read from input.txt file instead of standard(keyboard) input.
	   To test your program, you may save input data in input.txt file,
	   and use freopen function to read from the file when using cin function.
	   You may remove the comment symbols(//) in the below statement and use it.
	   Use #include<cstdio> or #include <stdio.h> to use the function in your program.
	   But before submission, you must remove the freopen function or rewrite comment symbols(//).
	 */	

	freopen("4_input.txt", "r", stdin);

	cin >> T;
	for(test_case = 0; test_case  < T; test_case++)
	{

		Answer = do_task();
		/////////////////////////////////////////////////////////////////////////////////////////////
		/*
		   Implement your algorithm here.
		   The answer to the case will be stored in variable Answer.
		 */
		/////////////////////////////////////////////////////////////////////////////////////////////
		
		// Print the answer to standard output(screen).
		cout << "Case #" << test_case+1 << endl;
		if(Answer) {
			cout << "YES" << endl;
		} else {
			cout << "NO" << endl;
		}
	}

	return 0;//Your program should return 0 on normal termination.
}