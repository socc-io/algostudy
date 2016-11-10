#include <iostream>
#include <vector>

using namespace std;

class Vertex{
public:
	int v[3];
	Vertex() {

	}
	Vertex(int a, int b, int c) {
		v[0] = a;
		v[1] = b;
		v[2] = c;
	}
	Vertex& operator=(const Vertex &other) {
		v[0] = other.v[0];
		v[1] = other.v[1];
		v[2] = other.v[2];
	}
	Vertex operator+(const Vertex &other) {
		Vertex res(
			v[0] + other.v[0],
			v[1] + other.v[1],
			v[2] + other.v[2]);
		return res;
	}
	Vertex operator-(const Vertex &other) {
		Vertex res(
			v[0] - other.v[0],
			v[1] - other.v[1],
			v[2] - other.v[2]);
		return res;
	}
	Vertex operator*(const Vertex &other) {
		Vertex res(
			v[0] * other.v[0],
			v[1] * other.v[1],
			v[2] * other.v[2]);
		return res;
	}
	Vertex operator*(const int k) {
		Vertex res(
			v[0] * k,
			v[1] * k,
			v[2] * k);
		return res;
	}
	int reduce() {
		return v[0] + v[1] + v[2];
	}
	int dot(Vertex &other) {
		return ((*this)*other).reduce();
	}
	Vertex cross(Vertex &other) {
		Vertex res(
			v[1] * other.v[2] - v[2] * other.v[1],
			v[2] * other.v[0] - v[0] * other.v[2],
			v[0] * other.v[1] - v[1] * other.v[0]);
		return res;
	}
};

bool includeTri(int x1, int y1, int x2, int y2, int kx, int ky)
{
	int det = x1 * y2 - x2 * y1;
	if(abs(det) < 0.0001f) return true;
	int t1 = y2 * kx - x2 * ky;
	int t2 = -y1 * kx + x1 * ky;
	if(0 <= t1 && t1 <= det && 0 <= t2 && t2 <= det && t1 + t2 <= det) return true;
	return false;
}

void DO()
{
	Vertex v[2][3];
	int coll_cnt = 0;
	for(int i=0;i<2;++i)for(int j=0;j<3;++j)for(int k=0;k<3;++k)cin >> v[i][j].v[k];
	Vertex plane_origin = v[0][0];
	Vertex a = v[0][1] - v[0][0];
	Vertex b = v[0][2] - v[0][0];
	Vertex plane_direction = a.cross(b);
	for(int i=0;i<2;++i) {
		for(int j=i+1;j<3;++j) {
			Vertex line_origin = v[1][i];
			Vertex line_direction = v[1][j] - line_origin;
			int t_rank = line_direction.dot(plane_direction);
			if(abs(t_rank) < 0.0001f) continue;
			int constant = (plane_origin - line_origin).dot(plane_direction);
			if(constant*t_rank < 0 || abs(t_rank) < abs(constant)) continue;
			Vertex cPoint = line_origin * t_rank + (line_direction * constant);
			int checker = 0;
			// cout << "Found CPoint: " << cPoint.v[0] << ", " << cPoint.v[1] << ", " << cPoint.v[2];
			Vertex delta = cPoint - (v[0][0] * t_rank);
			Vertex exp_a = a * t_rank;
			Vertex exp_b = b * t_rank;
			if(includeTri(exp_a.v[0], exp_a.v[1], exp_b.v[0], exp_b.v[1], delta.v[0], delta.v[1]) && includeTri(exp_a.v[0], exp_a.v[2], exp_b.v[0], exp_b.v[2], delta.v[0], delta.v[2])) {
				coll_cnt++;
				// cout << " : COLL!" << endl;
			} else {
				// cout << endl;
			}
		}
	}
	// cout << "COLL CNT: " << coll_cnt << endl;
	cout << (coll_cnt == 1 ? "YES" : "NO") << endl;
}

int main(int argc, char** argv)
{
	int T;
	cin >> T;
	for(int i=0;i<T;++i) {
		DO();
	}
	return 0;
}